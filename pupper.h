#ifndef HYGGE_PUPPER_H
#define HYGGE_PUPPER_H

#include "game_object.h"

class Pupper : public Game_object {
public:
    Pupper(sdlxx::Sdl_renderer& renderer, int x, int y);
    void update() override;
    void draw(sdlxx::Sdl_renderer& renderer) override;
    void collide(Game_object &rhs) override;

    bool isHeld() { return held; }

private:
    int frame = 0;
    sdlxx::Sdl_texture texture;
    bool held = false;
};

#endif
