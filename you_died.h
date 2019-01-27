#ifndef HYGGE_YOU_DIED_H
#define HYGGE_YOU_DIED_H

#include "scene.h"

class You_died : public Scene {
public:
    You_died(sdlxx::Sdl_renderer& renderer);

    void update() override;
    void draw(sdlxx::Sdl_renderer& renderer) override;

private:
    sdlxx::Sdl_renderer & _renderer;
    sdlxx::Sdl_texture _tex;
};

#endif
