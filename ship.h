#ifndef HYGGE_SHIP_H
#define HYGGE_SHIP_H

#include "game_object.h"
#include "vec2.h"
#include "include/sdlxx.h"

class Ship : public Game_object {
public:
    Ship(sdlxx::Sdl_renderer & ren);
    void update() override;
    void draw(sdlxx::Sdl_renderer & ren) override;

private:
    // These are components of the animation
    static constexpr int SHIP_FRAMES = 4;
    SDL_Rect clips[SHIP_FRAMES];
    unsigned frame = 0;

    sdlxx::Sdl_texture tex;

    double heading_deg = 0.0;
    double x = 0.0;
    double y = 0.0;
    Vec2 velocity;
};

#endif
