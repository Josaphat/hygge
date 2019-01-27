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
    move_speed = rand() % 9 + 2;
    air_move_speed = move_speed - 1;
    gravity = rand() % 3 + 3;

    move_right = rand() % 2;
}

void MoverPup::update()
{
    int jumpchance = rand() % 100;
    if ((velocity.y == 0) && (jumpchance < 1)) {
        velocity.y -= gravity * 8 - 1; // -1 so the puppers can't doublejump
    }
    Mover::update();
}
