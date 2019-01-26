#include "ship.h"
#include "input_map.h"
#include "screen_config.h"
#include <cmath>

Ship::Ship(sdlxx::Sdl_renderer & ren)
    : tex {"resources/ship.bmp", ren}
{
    // Set sprite clips
    clips[0].x = 0;
    clips[0].y = 0;
    clips[0].w = 63;
    clips[0].h = 63;

    clips[1].x = 63;
    clips[1].y = 0;
    clips[1].w = 63;
    clips[1].h = 63;

    clips[2].x = 0;
    clips[2].y = 63;
    clips[2].w = 63;
    clips[2].h = 63;

    clips[3].x = 63;
    clips[3].y = 64;
    clips[3].w = 63;
    clips[3].h = 62;
}

void Ship::update()
{
    if (input_state.rotate_left) { heading_deg -= 1.5; }
    if (input_state.rotate_right) { heading_deg += 1.5; }
    if (input_state.accelerate) {
        // We accelerate in the direction of the heading
        auto del_v = Vec2{};
        del_v.x = std::sin(heading_deg * 0.0174533) * .1;
        del_v.y = -std::cos(heading_deg * 0.0174533) * .1;

        velocity.x += del_v.x;
        velocity.y += del_v.y;

        ++frame;
        if ((frame / 4) >= SHIP_FRAMES) { frame = 12; }
    }
    else {
        frame = 0;
    }

    x += velocity.x;

    // Wrap
    if (x > (window_width + 62)) { x = -62; }
    if (x < -62) { x = window_width + 62; }

    y += velocity.y;
    // Wrap
    if (y > window_height) { y = -62; }
    if (y < -62) { y = window_height - 62; }
}

void Ship::draw(sdlxx::Sdl_renderer & ren)
{
    ren.copy(tex, int(x), int(y), &clips[frame / 4], heading_deg);
}
