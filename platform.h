#ifndef HYGGE_PLATFORM_H
#define HYGGE_PLATFORM_H

#include "game_object.h"

class Platform : public Game_object {
public:
    Platform(int x, int y, int width, int height)
        : x{x}, y{y}, width{width}, height{height}
    {
    }

    void update() override
    {
    }

    void draw(sdlxx::Sdl_renderer & renderer) override
    {
        renderer.fill_rect(x, y, width, height, 255, 0, 0);
    }

private:
    int x;
    int y;
    int width;
    int height;
};

#endif
