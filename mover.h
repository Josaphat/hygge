#ifndef HYGGE_MOVER_H
#define HYGGE_MOVER_H

#include "game_object.h"
#include "vec2.h"

class Mover : public Game_object {
public:
    Mover(sdlxx::Sdl_renderer& renderer, int height, int width, int x_pos, int ypos, std::string path);
    void update() override;
    void draw(sdlxx::Sdl_renderer& renderer) override;
    void collide(Game_object& rhs) override;

protected:
    const int move_speed = 5;
    const int air_move_speed = 5;
    const int gravity = 2;

    bool move_right = true;

    sdlxx::Sdl_texture texture;
};

#endif
