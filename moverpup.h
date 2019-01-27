#ifndef HYGGE_MOVERPUP_H
#define HYGGE_MOVERPUP_H

#include "mover.h"
#include "vec2.h"

class MoverPup : public Mover {
public:
    MoverPup(sdlxx::Sdl_renderer& renderer, int x_pos, int ypos);
    void update() override;
};

#endif
