#ifndef HYGGE_FIRE_H
#define HYGGE_FIRE_H

#include "game_object.h"
#include "include/sdlxx.h"

using namespace sdlxx;

class Fire : public Game_object {
public:
    Fire(sdlxx::Sdl_renderer& renderer, int x, int y)
        : Game_object{120,
                      120,
                      {static_cast<double>(x), static_cast<double>(y)},
                      {0, 0} }//,
        //texture{ "fire.bmp", renderer }
    {
        isPlatform = false;
    }

    void update() override {
    }

    void draw(sdlxx::Sdl_renderer& renderer) override
    {
        auto texture = Sdl_texture{ "fireplace.bmp", renderer };
        SDL_Rect clip;
        clip.x = (currentFrame / 4) * 112;
        clip.y = 0;
        clip.h = 112;
        clip.w = 109;

        SDL_Rect dest;
        dest.x = position.x;
        dest.y = position.y;
        dest.h = height;
        dest.w = width;
        SDL_RenderCopyEx(renderer, texture, &clip, &dest, 0,
            /*center=*/nullptr, SDL_FLIP_NONE);

        ++currentFrame;
        if (currentFrame / 4 >= FRAMES) {
            currentFrame = 0;
        }
    }
private:
    //sdlxx::Sdl_texture texture;
    int currentFrame{ 0 };
    const int FRAMES = 4;
};

#endif
