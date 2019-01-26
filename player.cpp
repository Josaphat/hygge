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
        position.x -= velocity;
    }
    if (input_state.move_right) {
        position.x += velocity;
    }
}

void Player::draw(sdlxx::Sdl_renderer & renderer)
{
    renderer.fill_rect(position.x, position.y, width, height,
                       0, 255, 0);
}
