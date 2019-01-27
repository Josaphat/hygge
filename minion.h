#ifndef HYGGE_MINION_H
#define HYGGE_MINION_H

#include "mover.h"
#include "vec2.h"

class Minion : public Mover {
public:
    Minion(sdlxx::Sdl_renderer& renderer, int x_pos, int ypos);
};

#endif
