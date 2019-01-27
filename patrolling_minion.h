#ifndef HYGGE_PATROLLING_MINION_H
#define HYGGE_PATROLLING_MINION_H

#include "mover.h"
#include "vec2.h"

class Patrolling_Minion : public Mover {
public:
    Patrolling_Minion(sdlxx::Sdl_renderer& renderer, int x_pos, int ypos);

	void collide(Game_object& rhs) override;
};

#endif
