#pragma once
#include "dungeon_types.h"
namespace dungeon_demo
{
    // forward declared
    class dungeon;
    class builder;

    class base_strategy
    {
    public:
        base_strategy() = default;
        virtual ~base_strategy() = default;
        // pass in builder to carry some info
        virtual dungeon do_generate(const builder& builder) = 0;
    protected:
        void fill_with(dungeon&, dungeon_demo::types, size_t row, size_t col, size_t row_len, size_t col_len);
        void set_tile(dungeon&, dungeon_demo::types, size_t row, size_t col);
    };
    
    class linear : public base_strategy {
    public:
        dungeon do_generate(const builder& builder) override;
    };

    // helper struct and functions
    struct point {
        int x = -1;
        int y = -1;
        point() = default;
        point(size_t in_x, size_t in_y)
            : x(in_x), y(in_y) {}
        bool operator==(const point& other) const;
        bool operator!=(const point& other) const;
    };

    struct edge {
        point p0;
        point p1;
        size_t weight = 0;
        edge(point in_p0, point in_p1)
            : p0(in_p0), p1(in_p1)
        {}

        bool operator==(const edge& other) const;
    };
    
    struct a_star {
        struct node {
            point p;
            int cost = 0;
            int parent_idx = -1;
            bool operator==(const point& other) const;
        };

        std::vector<edge> operator()(const dungeon& in_dungeon, const point& src, const point& dst);
    };
    // end of helper struct and functions
} // namespace dungeon_demo
