#include "generate_strategy.h"
#include "dungeon.h"
#include <algorithm>
#include <unordered_set>
#include <queue>

// TODO: make these constexpr static members
constexpr int room_min_width = 4;
constexpr int room_max_width = 8;
constexpr int room_min_height = 4;
constexpr int room_max_height = 8;

constexpr int corridor_min_length = 4;
constexpr int corridor_max_length = 10;

constexpr int corridor_width = 1;

template<>
struct std::hash<dungeon_demo::point>
{
    std::size_t operator()(const dungeon_demo::point& s) const noexcept
    {
        return s.x << 16 | s.y;
    }
};

size_t dist(const dungeon_demo::point& p1, const dungeon_demo::point& p2)
{
    size_t dx = std::abs(p1.x - p2.x);
    size_t dy = std::abs(p1.y - p2.y);
    return dx + dy;
}

// struct cost_func {
//     cost_func(const dungeon_demo::point& in_src, const dungeon_demo::point& in_dst)
//         : src(in_src), dst(in_dst) {}
//     size_t operator()(const dungeon_demo::point& in_point)
//     {
//         return distance(src, in_point) + distance(dst, in_point);
//     }
//     const dungeon_demo::point& src;
//     const dungeon_demo::point& dst;
// };


bool operator!=(const dungeon_demo::point& lhs, const dungeon_demo::point& rhs)
{
    return !(lhs==rhs);
}

bool dungeon_demo::point::operator==(const point &other) const
{
    return x == other.x && y == other.y;
}

bool dungeon_demo::point::operator!=(const point &other) const
{
    return !((*this) == other);
}

bool dungeon_demo::edge::operator==(const edge &other) const
{
    if(p0 == other.p0 && p1 == other.p1)
        return true;
    if(p0 == other.p1 && p1 == other.p0)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& os, const dungeon_demo::point& p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}

uint8_t operator&(const dungeon_demo::direction& lhs, const dungeon_demo::direction& rhs)
{
    return static_cast<uint8_t>(lhs) & static_cast<uint8_t>(rhs);
}

dungeon_demo::dungeon dungeon_demo::linear::do_generate(const builder& builder)
{
    dungeon new_dungeon(builder.get_row_len(), builder.get_col_len());
    
    fill_with(new_dungeon, types::None, 1, 1, builder.get_row_len() - 2, builder.get_col_len() - 2);

    std::vector<point> rooms_center;

    size_t rooms_generated = 0;
    // randomly place some rooms

    for(auto attempt = 0; attempt < 1000; ++attempt)
    {
        size_t random_row_len = builder::random_int(room_min_height, room_max_height);
        size_t random_col_len = builder::random_int(room_min_width, room_max_width);
        size_t random_row = builder::random_int(1, new_dungeon.get_row_length());
        size_t random_col = builder::random_int(1, new_dungeon.get_col_length());
        // make sure there is no adjacent room
        if(new_dungeon.check_tiles_available(random_row - 1, random_col - 1, random_row_len + 2, random_col_len + 2))
        {
            fill_with(new_dungeon, types::Wall, random_row, random_col, random_row_len, random_col_len);
            fill_with(new_dungeon, types::Room, random_row + 1, random_col + 1, random_row_len - 2, random_col_len - 2);
            size_t center_x = random_row + random_row_len / 2;
            size_t center_y = random_col + random_col_len / 2;
            rooms_center.emplace_back(center_x, center_y);
            if(++rooms_generated == builder.get_rooms_to_gen())
                break;
        }
    }
    std::sort(rooms_center.begin(), rooms_center.end(), [](const point& p1, const point& p2){
        if(p1.x > p2.x)
            return true;
        else if(p1.x == p2.x)
        {
            if(p1.y > p2.y)
                return true;
        }
        return false;
    });
    for(int i = 0; i < builder.get_rooms_to_gen() - 1; ++i)
    {
        auto shortest_path = a_star()(new_dungeon, rooms_center[i], rooms_center[i+1]);
        for(const auto path : shortest_path)
        {
            switch (new_dungeon.get_tile(path.p0.x, path.p0.y))
            {
            case types::Wall:
                set_tile(new_dungeon, types::Door, path.p0.x, path.p0.y);
                break;
            case types::None:
                set_tile(new_dungeon, types::Corridor, path.p0.x, path.p0.y);
                break;
            default:
                break;
            }
        }
    }
    
    return new_dungeon;
}

void dungeon_demo::base_strategy::fill_with(dungeon & in_dungeon, dungeon_demo::types in_type, size_t row, size_t col, size_t row_len, size_t col_len)
{
    for(size_t i = row; i < row + row_len; ++i)
    {
        std::fill(in_dungeon.data_.begin() + i * in_dungeon.col_length_ + col, in_dungeon.data_.begin() + i * in_dungeon.col_length_ + col + col_len, in_type);
    }
}

void dungeon_demo::base_strategy::set_tile(dungeon & in_dungeon, dungeon_demo::types in_type, size_t row, size_t col)
{
    in_dungeon.data_[row * in_dungeon.col_length_ + col] = in_type;
}

bool dungeon_demo::a_star::node::operator==(const point &other) const
{
    return p == other;
}

std::vector<dungeon_demo::edge> dungeon_demo::a_star::operator()(const dungeon &in_dungeon, const point &src, const point &dst)
{
    auto comp = [&](const node& p1, const node& p2){
        return p1.cost > p2.cost;
    };
    std::vector<edge> shortest_path;

    std::priority_queue<node, std::vector<node>, decltype(comp)> open_set(comp);
    std::unordered_set<point> inserted;
    std::vector<node> close_set;
    node src_node;
    src_node.p = src;
    open_set.push(std::move(src_node));

    while(!open_set.empty())
    {
        auto& cur = open_set.top();
        if(cur.p == dst)
        {
            auto parent_node = close_set[cur.parent_idx];
            while(parent_node.parent_idx != -1)
            {
                shortest_path.emplace_back(parent_node.p, cur.p);
                parent_node = close_set[parent_node.parent_idx];;
            }
            break;
        }
        auto [cur_x, cur_y] = cur.p;
        close_set.push_back(std::move(cur));
        open_set.pop();

        // vertical
        for(int i = -1; i < 2; i += 2)
        {
            if(cur_x + i > 0 && cur_x + i < in_dungeon.get_row_length() - 1
            && inserted.find(point(cur_x + i, cur_y)) == inserted.end()
            && std::find(close_set.begin(), close_set.end(), point(cur_x + i, cur_y)) == close_set.end())
            {
                node new_open;
                new_open.p = point(cur_x + i, cur_y);
                new_open.parent_idx = close_set.size() - 1;
                new_open.cost = dist(new_open.p, src) + dist(new_open.p, dst);
                if(in_dungeon.get_tile(cur_x + i, cur_y) == types::Room)
                {
                    new_open.cost -= 10;
                }
                else if(in_dungeon.get_tile(cur_x + i, cur_y) == types::Wall)
                {
                    new_open.cost += 10;
                }
                open_set.push(std::move(new_open));
                inserted.insert(new_open.p);
            }
        }
        // horizontal
        for(int i = -1; i < 2; i += 2)
        {
            if(cur_y + i > 0 && cur_y + i < in_dungeon.get_col_length() - 1
            && inserted.find(point(cur_x, cur_y + i)) == inserted.end()
            && std::find(close_set.begin(), close_set.end(), point(cur_x, cur_y + i)) == close_set.end())
            {
                node new_open;
                new_open.p = point(cur_x, cur_y + i);
                new_open.parent_idx = close_set.size() - 1;
                new_open.cost = dist(new_open.p, src) + dist(new_open.p, dst);
                if(in_dungeon.get_tile(cur_x, cur_y + i) == types::Room)
                {
                    new_open.cost -= 10;
                }
                else if(in_dungeon.get_tile(cur_x, cur_y + i) == types::Wall)
                {
                    new_open.cost += 10;
                }
                open_set.push(std::move(new_open));
                inserted.insert(new_open.p);
            }
        }
    }
    return shortest_path;
}