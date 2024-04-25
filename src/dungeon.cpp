#include "dungeon.h"
#include <cassert>
#include <algorithm>
#include <fstream>

std::random_device rd;
std::mt19937 dungeon_demo::builder::mt(rd());

dungeon_demo::dungeon::dungeon(size_t size_x, size_t size_y)
    : row_length_(size_x), col_length_(size_y), data_(size_x * size_y,  types::Wall)
{
}

dungeon_demo::dungeon::dungeon(const dungeon && other)
    : row_length_(other.row_length_), col_length_(other.col_length_), data_(std::move(other.data_))
{
}

void dungeon_demo::dungeon::show() const
{
    for(auto i = 0; i < row_length_; ++i)
    {
        for(auto j = 0; j < col_length_; ++j)
            std::cout << static_cast<char>(get_tile(i, j)) << ' ';
        std::cout << '\n';
    }
}


void dungeon_demo::dungeon::write() const
{
    std::ofstream dungeon_file("../out/dungeon.txt");
    for(auto i = 0; i < row_length_; ++i)
    {
        for(auto j = 0; j < col_length_; ++j)
            dungeon_file << static_cast<char>(get_tile(i, j)) << ' ';
        dungeon_file << '\n';
    }
    dungeon_file.close();
}


dungeon_demo::types dungeon_demo::dungeon::get_tile(size_t row, size_t col) const
{
    assert(row >= 0 && row < row_length_ && "row is out of bounds");
    assert(col >= 0 && col < col_length_ && "col is out of bounds");
    return data_[col_length_ * row + col];
}


dungeon_demo::dungeon dungeon_demo::builder::build()
{
    std::cout << "generating dungeon with width = " << dungeon_width_ << " and height = " << dungeon_height_ << '\n';
    
    if(generate_strategy_)
        return generate_strategy_->do_generate(*this);
    return dungeon(dungeon_width_, dungeon_height_);
}

int dungeon_demo::builder::random_int(int min, int max)
{
    std::uniform_int_distribution dis(min, max);
    return dis(mt);
}

bool dungeon_demo::dungeon::check_tiles_available(size_t row, size_t col, size_t row_len, size_t col_len)
{
    // dungeon is surrounded with wall
    if(row <= 0 || col <= 0 || row + row_len >= row_length_ || col + col_len >= col_length_)
        return false;
    
    for(size_t i = row; i < row + row_len; ++i)
    {
        for(size_t j = col; j < col + col_len; ++j)
        {
            if(data_[i * col_length_ + j] != types::None)
                return false;
        }
    }

    return true;
}