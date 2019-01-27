#ifndef HYGGE_MOVERPUP_H
#define HYGGE_MOVERPUP_H

#include "mover.h"
#include "vec2.h"
#include "game_object.h"

class MoverPup : public Mover {
public:
    MoverPup(sdlxx::Sdl_renderer& renderer, int x_pos, int ypos);
    void update() override;
    void collide(Game_object& rhs) override;
};

#endif
