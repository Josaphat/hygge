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
    SDL_Rect rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.w = width;
    rect.h = height;
    SDL_RendererFlip flip {SDL_FLIP_NONE};
    if (move_right) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0.0, NULL, flip);
}

void Mover::collide(Game_object& rhs)
{
    if (velocity.y > gravity) {
        printf("velocityy: %f\n", velocity.y);
    }
    if (rhs.isPlatform && velocity.y > 0) {
        // We're falling
        double overlap_y;
        if (position.y <= rhs.position.y) {
            overlap_y = (position.y + height) - rhs.position.y;

        }
        else {
            overlap_y = (rhs.position.y + rhs.height) - position.y;

        }
        //bool overlap_x = ((position.x > rhs.position.x) && (position.x <= rhs.position.x + rhs.width))
        //    || ((position.x + width > rhs.position.x) && (position.x + width <= rhs.position.x + rhs.width));
        double overlap_x;
        if (position.x < rhs.position.x) {
            overlap_x = position.x + width - rhs.position.x;
        }
        else {
            overlap_x = rhs.position.x + rhs.width - position.x;
        }

        if (overlap_y > 0 && overlap_x >= velocity.x) {
            // We're starting to go through a platorm.
            // Move the player back up so they're not through the platform.
            position.y -= overlap_y;
            velocity.y = -gravity;
        }
    }
}
