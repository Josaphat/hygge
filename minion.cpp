#include "minion.h"
#include "screen_config.h"
#include "input_map.h"

Minion::Minion()
    : Game_object{50, 50, {100, static_cast<double>(window_height - 75)}, {0,0}}
{
}

void Minion::update()
{
    if (move_right) {
        position.x += move_speed;
    }
	else{
        position.x -= move_speed;
    }

	//if we're going to run off the scene switch directions
	if (position.x >= window_width - 45 || position.x <= 25) {
		move_right = !move_right;
	}

    velocity.y += gravity;
    position.y += velocity.y;
}

void Minion::draw(sdlxx::Sdl_renderer & renderer)
{
    renderer.fill_rect(position.x, position.y, width, height,
                       0, 0, 255);
}

void Minion::collide(Game_object & rhs)
{
    if (velocity.y > 0) {
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
