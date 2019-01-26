#ifndef HYGGE_PLAYER_H
#define HYGGE_PLAYER_H

#include "game_object.h"
#include "vec2.h"

class Player : public Game_object {
public:
    Player();
    void update() override;
    void draw(sdlxx::Sdl_renderer & renderer) override;

public:
    const int width = 50;
    const int height = 75;
    Vec2 position {0, 0};
    Vec2 velocity {0, 0};

private:

    const int move_speed = 5;
    const int air_move_speed = 5;
    const int gravity = 2;

    bool jumping = false;
    bool ready_for_double_jump = false;
    bool double_jump = false;
    int jump_frame = 0;
};

#endif
