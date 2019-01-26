#ifndef HYGGE_MINION_H
#define HYGGE_MINION_H

#include "game_object.h"
#include "vec2.h"

class Minion : public Game_object {
public:
    Minion(sdlxx::Sdl_renderer& renderer);
    Minion(sdlxx::Sdl_renderer& renderer, int x_pos, int ypos);
    void update() override;
    void draw(sdlxx::Sdl_renderer& renderer) override;
    void collide(Game_object& rhs) override;

private:
    const int move_speed = 5;
    const int air_move_speed = 5;
    const int gravity = 2;

    bool move_right = true;

    sdlxx::Sdl_texture texture;
};

#endif
