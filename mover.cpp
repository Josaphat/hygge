#include "mover.h"
#include "input_map.h"
#include "screen_config.h"

Mover::Mover(sdlxx::Sdl_renderer& renderer, int height, int width, int x_pos, int y_pos, std::string path)
    : Game_object{height,
                  width,
                  {static_cast<double>(x_pos), static_cast<double>(y_pos)},
                  {0, 0},
                  true},
    texture{path, renderer }
{
    isPlayer = false;
    isVillain = true;
}

void Mover::update()
{
    if (move_right) { position.x += move_speed; }
    else {
        position.x -= move_speed;
    }

    // if we're going to run off the scene switch directions
    if (position.x >= window_width - 45 || position.x <= 25) {
        move_right = !move_right;
    }

    velocity.y += gravity;
    position.y += velocity.y;
}

void Mover::draw(sdlxx::Sdl_renderer& renderer)
{
    renderer.draw_rect(position.x, position.y, width, height, 0, 0, 255);
    renderer.copy(texture, int(position.x), int(position.y));
}

void Mover::collide(Game_object& rhs)
{
    if (rhs.can_be_destroyed == false && velocity.y > 0) {
        // We're falling
        auto overlap_y = (position.y + height) - rhs.position.y;
        if (overlap_y > 0) {
            // We're starting to go through a platform.
            // Move the player back up so they're not through the platform.
            position.y -= overlap_y;
            velocity.y = 0;
        }
    }
}
