#ifndef HYGGE_HOME_SCENE_H
#define HYGGE_HOME_SCENE_H

#include "scene.h"

class Home_scene : public Scene {
public:
    Home_scene(sdlxx::Sdl_renderer& renderer);
    void update() override;

private:
    int pups = 0;
    sdlxx::Sdl_renderer& renderer;
};

#endif
