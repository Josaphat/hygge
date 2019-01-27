#ifndef HYGGE_PLATFORMING_SCENE_H
#define HYGGE_PLATFORMING_SCENE_H

#include "scene.h"

class Platforming_scene : public Scene {
public:
    Platforming_scene(sdlxx::Sdl_renderer& renderer);
    void update() override;
    void setNeedPups(bool doNeedPups) { needPups = doNeedPups; }
private:
    int pups{ 0 };
    bool needPups{ false };
    sdlxx::Sdl_renderer& _renderer;
};

#endif
