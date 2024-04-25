#include "dungeon.h"

int main() {
    dungeon_demo::builder dungeon_builder;

    dungeon_demo::dungeon my_dunegon = dungeon_builder.set_dungeon_width(30)
    .set_dungeon_height(40)
    .set_rooms_to_generate(12)
    .set_generate_strategy(std::make_unique<dungeon_demo::linear>())
    .build();

    my_dunegon.show();
    my_dunegon.write();
    std::cout << "press any key to quit\n";
    std::cin.get();
    return 0;
}