# A simple Dungeon generator


## Build Status
| Platform | Status   |
| -------- | -------- |
| Windows  | [![build windows](https://github.com/frankpyf/COMP7107_management_of_complex_data_types/actions/workflows/cmake_build_windows.yml/badge.svg)](https://github.com/frankpyf/COMP7107_management_of_complex_data_types/actions/workflows/cmake_build_windows.yml) |
| MacOS  | [![build macos](https://github.com/frankpyf/COMP7107_management_of_complex_data_types/actions/workflows/cmake_build_macos.yml/badge.svg)](https://github.com/frankpyf/COMP7107_management_of_complex_data_types/actions/workflows/cmake_build_macos.yml) |
| Linux  | [![build linux](https://github.com/frankpyf/COMP7107_management_of_complex_data_types/actions/workflows/cmake_build_linux.yml/badge.svg)](https://github.com/frankpyf/COMP7107_management_of_complex_data_types/actions/workflows/cmake_build_linux.yml) |


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