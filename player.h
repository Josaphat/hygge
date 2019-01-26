#ifndef HYGGE_PLAYER_H
#define HYGGE_PLAYER_H

#include "game_object.h"
#include "vec2.h"

class Player : public Game_object {
public:
    Player();
    void update() override;
    void draw(sdlxx::Sdl_renderer & renderer) override;

private:
    const int width = 50;
    const int height = 75;
    Vec2 position;
};

#endif
