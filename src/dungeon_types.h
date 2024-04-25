#pragma once
#include <cstdint>
#include <vector>
#include <iostream>

namespace dungeon_demo
{
    enum class types : char {
        None        = ' ',
        Wall        = 'W',
        Room        = '#',
        Corridor    = '.',
        Door        = 'D',
    };
    
    
    enum class direction : uint8_t {
        North           = 1,
        South           = 2,
        East            = 4,
        West            = 8,
        EveryDirection  = 15,
    };
} // namespace dungeon_demo
