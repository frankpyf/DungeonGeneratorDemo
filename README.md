# A simple Dungeon generator


## Build Status
| Platform | Status   |
| -------- | -------- |
| Windows, Linux, macOS  | [![build](https://github.com/frankpyf/DungeonGeneratorDemo/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/frankpyf/DungeonGeneratorDemo/actions/workflows/cmake-multi-platform.yml) |


# Features
one simple generate strategy using A* algorithm.
```
W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W 
W                                                         W 
W                                                         W 
W                     W W W W W W W   W W W W W W W W     W 
W                     W # # # # # W   W # # # # # # W     W 
W                     W # # # # # W   W # # # # # # W     W 
W                     W # # # # # D . W # # # # # # W     W 
W                     W # # # # # W . W # # # # # # W     W 
W     W W W W         W W W W W W W . W # # # # # # W     W 
W     W # # W       . . . . . . . . . D # # # # # # W     W 
W     W # # D . . . .                 W W W W W W W W     W 
W     W W W W   . W W W W                                 W 
W               . W # # W                                 W 
W               . W # # W                                 W 
W               . W W D W     W W W W W W                 W 
W               . . . . . . . W # # # # W                 W 
W               W W W W     . W # # # # W                 W 
W               W # # W     . W # # # # W     W W W W W   W 
W               W # # W     . W # # # # W     W # # # W   W 
W               W # # W . . . D # # # # W     W # # # W   W 
W               W # # W .     W W W W W W     W # # # W   W 
W               W # # D . . . . . . . . . . . W # # # W   W 
W               W W W W   W W W W . . . . . . D # # # W   W 
W                         W # # W .           W # # # W   W 
W                         W # # W .           W W W W W   W 
W   W W W W               W # # D .                       W 
W   W # # W . . . . . . . W # # W                         W 
W   W # # D . W W W W W . D # # W                         W 
W   W W W W . W # # # W   W W W W                         W 
W           . W # # # W                                   W 
W           . D # # # W                                   W 
W   W W W W . W W W W W         W W W W W W W W           W 
W   W # # W .                   W # # # # # # W           W 
W   W # # D . . . . . . . . . . D # # # # # # W           W 
W   W W W W                     W W W W W W W W           W 
W                                                         W 
W                                                         W 
W                                                         W 
W                                                         W 
W W W W W W W W W W W W W W W W W W W W W W W W W W W W W W 
```

# TODOs
More generate strategy:

[vazgriz](https://vazgriz.com/119/procedurally-generated-dungeons/), 
[mike anderson](https://roguebasin.com/index.php/Dungeon-Building_Algorithm) s
etc.

clean up the code.