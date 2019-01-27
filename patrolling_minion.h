#ifndef HYGGE_PATROLLING_MINION_H
#define HYGGE_PATROLLING_MINION_H

#include "game_object.h"
#include "vec2.h"

class Patrolling_Minion : public Game_object {
public:
    Patrolling_Minion(sdlxx::Sdl_renderer& renderer, int x_pos, int ypos);
	void update() override;
	void draw(sdlxx::Sdl_renderer& renderer) override;
	void collide(Game_object& rhs) override;

protected:
	int move_speed = 5;
	int air_move_speed = 5;
	int gravity = 2;

	bool move_right = true;

	sdlxx::Sdl_texture texture;
};

#endif
