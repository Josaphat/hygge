#include "moverpup.h"

MoverPup::MoverPup(sdlxx::Sdl_renderer& renderer, int x_pos, int y_pos)
    : Mover{renderer,
            35,
            50,
            x_pos,
            y_pos,
            "resources/pupper.bmp" }
{
    isPlayer = false;
    isVillain = false;
    move_speed = rand() % 10 + 1;
    air_move_speed = move_speed;
    gravity = 5;

    move_right = rand() % 2;
}
