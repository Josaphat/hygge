#include "player.h"
#include "screen_config.h"
#include "input_map.h"

Player::Player()
    : position{0, static_cast<double>(window_height - height)}
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

    if (jumping) {
        ++jump_frame;

        velocity.y += gravity;
        position.y += velocity.y;
        if (position.y >= window_height - height) {
            position.y = window_height - height;
            jumping = false;
            double_jump = false;
        }
    }
}

void Player::draw(sdlxx::Sdl_renderer & renderer)
{
    renderer.fill_rect(position.x, position.y, width, height,
                       0, 255, 0);
}
