#ifndef HYGGE_GOAL_H
#define HYGGE_GOAL_H

#include "game_object.h"
#include "include/sdlxx.h"

class Goal : public Game_object {
public:
    Goal(sdlxx::Sdl_renderer& renderer, int x, int y)
        : Game_object{75,
                      50,
                      {static_cast<double>(x), static_cast<double>(y)},
                      {0, 0}},
          texture{"resources/mailbox.bmp", renderer}
    {
        isGoal = true;
    }

    void update() override {}
    void draw(sdlxx::Sdl_renderer& renderer) override
    {
        renderer.copy(texture, int(position.x), int(position.y));
    }

private:
    sdlxx::Sdl_texture texture;
};

#endif
