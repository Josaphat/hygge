#ifndef HYGGE_PLATFORMING_SCENE_H
#define HYGGE_PLATFORMING_SCENE_H

#include "goal.h"
#include "player.h"
#include "pupper.h"
#include "scene.h"

class Platforming_scene : public Scene {
public:
    Platforming_scene(sdlxx::Sdl_renderer& renderer);
    void update() override;

private:
    Player* player = nullptr;
    Pupper* pupper = nullptr;
    Goal* mailbox = nullptr;
    Vec2 player_spawn;
    int pups{0};
    sdlxx::Sdl_renderer& _renderer;
};

#endif
