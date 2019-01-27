#include "minion.h"
#include "input_map.h"
#include "screen_config.h"

Minion::Minion(sdlxx::Sdl_renderer& renderer, int x_pos, int y_pos)
    : Mover{renderer,
            50,
            50,
            x_pos,
            y_pos,
            "resources/minion.bmp"}
{
    isPlayer = false;
    isVillain = true;
}

