#ifndef HYGGE_NOT_A_PLATFORM_H
#define HYGGE_NOT_A_PLATFORM_H

#include "game_object.h"

class Not_A_Platform : public Game_object {
public:
    Not_A_Platform(int x, int y, int width, int height)
        : Game_object{height,
                      width,
                      {static_cast<double>(x), static_cast<double>(y)},
                      {0, 0}}
    {
        isPlatform = false;
    }

    void update() override {}

    void draw(sdlxx::Sdl_renderer& renderer) override
    {
        renderer.fill_rect(position.x, position.y, width, height, 255, 255,
                           255);
        renderer.fill_rect(position.x + 2, position.y + 2, width - 4,
                           height - 4, 0, 0, 0);
        renderer.fill_rect(position.x + 4, position.y + 4, width - 8,
                           height - 8, 255, 255, 255);
        renderer.fill_rect(position.x + 6, position.y + 6, width - 12,
                           height - 12, 0, 0, 0);
    }
};

#endif
