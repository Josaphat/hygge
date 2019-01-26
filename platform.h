#ifndef HYGGE_PLATFORM_H
#define HYGGE_PLATFORM_H

#include "game_object.h"

class Platform : public Game_object {
public:
    Platform(int x, int y, int width, int height)
        : Game_object{height,
                      width,
                      {static_cast<double>(x), static_cast<double>(y)},
                      {0, 0}}
    {
    }

    void update() override {}

    void draw(sdlxx::Sdl_renderer& renderer) override
    {
        renderer.fill_rect(position.x, position.y, width, height, 255, 0, 0);
    }
};

#endif
