#ifndef HYGGE_TUTORIAL_SCENE_H
#define HYGGE_TUTORIAL_SCENE_H

#include "platforming_scene.h"

class Tutorial_scene : public Scene {
public:
    Tutorial_scene(sdlxx::Sdl_renderer& renderer);
    Tutorial_scene(Tutorial_scene &&) = default;
    Tutorial_scene(const Tutorial_scene&) =delete;
    void update() override;

    void draw(sdlxx::Sdl_renderer& renderer) override;

private:
    sdlxx::Sdl_texture  _overlay;
};

#endif
