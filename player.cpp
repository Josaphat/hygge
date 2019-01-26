#include "player.h"
#include "screen_config.h"
#include "input_map.h"

Player::Player(sdlxx::Sdl_renderer & renderer)
    : Game_object{/*height*/75, /*width*/50, {0, static_cast<double>(window_height - 75)}, {0,0}}
    , texture {"resources/hyggens.bmp", renderer}
{
}

void Player::update()
{
    if (input_state.move_left) {
        position.x -= move_speed;
    }
    if (input_state.move_right) {
        position.x += move_speed;
    }

    if (input_state.jump && !jumping){
        jumping = true;
        velocity.y = -30;
        jump_frame = 0;
        ready_for_double_jump = false;
    }
    if (!ready_for_double_jump && jumping && !input_state.jump) {
        ready_for_double_jump = true;
    }
    if (ready_for_double_jump && input_state.jump && !double_jump) {
        double_jump = true;
        velocity.y = -30;
        jump_frame = 0;
    }

    velocity.y += gravity;
    position.y += velocity.y;

    if (jumping) {
        ++jump_frame;

        if (position.y >= window_height - height) {
            position.y = window_height - height;
            jumping = false;
            double_jump = false;
        }
    }
}

void Player::draw(sdlxx::Sdl_renderer & renderer)
{
    renderer.draw_rect(position.x, position.y, width, height, 0, 255, 0);
    renderer.copy(texture, int(position.x), int(position.y));
}

void Player::collide(Game_object & rhs)
{
    if (velocity.y > 0) {
        // We're falling
        auto overlap_x = (position.x + height) - rhs.position.x;
        auto overlap_y = (position.y + height) - rhs.position.y;
        if (overlap_y > 0) {
            // We're starting to go through a platform.
            // Move the player back up so they're not through the platform.
            position.y -= overlap_y;

            // They're no longer jumping
            jumping = false;
            double_jump = false;
            velocity.y = 0;
        }
    }
}
