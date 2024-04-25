#pragma once
#include "generate_strategy.h"
#include <unordered_set>
#include <memory>
#include <random>

namespace dungeon_demo
{
    struct rect {
        rect() = default;
        rect(size_t in_x, size_t in_y, size_t in_w, size_t in_h)
            : x(in_x), y(in_y), width(in_w), height(in_h) {}

        size_t x        = -1;
        size_t y        = -1;
        uint32_t width    = 0;
        uint32_t height   = 0;
    };

    class dungeon {
        using dungeon_data = std::vector<types>;

        dungeon_data data_;
        size_t row_length_ = 0;
        size_t col_length_ = 0;

        friend class base_strategy;
    public:
        dungeon(size_t size_x, size_t size_y);
        dungeon(const dungeon&&);

        types get_tile(size_t row, size_t col) const;

        void show() const;
        void write() const;

        size_t get_row_length() const { return row_length_; }
        size_t get_col_length() const { return col_length_; }

        bool check_tiles_available(size_t row, size_t col, size_t row_len, size_t col_len);
    };
    
    class builder {
        std::unique_ptr<base_strategy> generate_strategy_{};

        size_t rooms_to_generate_ = 0;
        size_t dungeon_width_ = 0;
        size_t dungeon_height_ = 0;

        static std::mt19937 mt;
    public:
        builder& set_rooms_to_generate(size_t room_num) { rooms_to_generate_ = room_num; return *this; }
        builder& set_dungeon_width(size_t width) { dungeon_width_ = width; return *this; }
        builder& set_dungeon_height(size_t height) { dungeon_height_ = height; return *this; }
        builder& set_generate_strategy(std::unique_ptr<base_strategy> new_strategy) 
        {
            generate_strategy_ = std::move(new_strategy); 
            return *this; 
        }
            
        [[nodiscard]] dungeon build();

        size_t get_rooms_to_gen() const { return rooms_to_generate_; }
        size_t get_row_len() const { return dungeon_height_; }
        size_t get_col_len() const { return dungeon_width_; }

        static int random_int(int min, int max);
    };
} // namespace dungeon
