#ifndef HYGGE_TUTORIAL_SCENE_H
#define HYGGE_TUTORIAL_SCENE_H

#include "platforming_scene.h"

class Tutorial_scene : public Scene {
public:
    Tutorial_scene(sdlxx::Sdl_renderer& /*renderer*/);
    void update() override;
};

#endif
