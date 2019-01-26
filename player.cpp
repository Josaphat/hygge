#include "player.h"
#include "screen_config.h"

Player::Player()
{
    position.x = 0;
    position.y = window_height - height;
}

void Player::update()
{
}

void Player::draw(sdlxx::Sdl_renderer & renderer)
{
    renderer.fill_rect(position.x, position.y, width, height,
                       0, 255, 0);
}
