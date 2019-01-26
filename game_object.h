#ifndef HYGGE_GAME_OBJECT_H
#define HYGGE_GAME_OBJECT_H

#include "include/sdlxx.h"

class Game_object {
public:
    virtual void update() = 0;
    virtual void draw(sdlxx::Sdl_renderer & renderer) = 0;
};

#endif
