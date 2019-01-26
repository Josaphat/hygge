#ifndef HYGGE_SCENE_H
#define HYGGE_SCENE_H

#include <vector>
#include <memory>
#include "game_object.h"
#include "include/sdlxx.h"

class Scene {
public:
    void update();
    void draw(sdlxx::Sdl_renderer & renderer);

protected:
    std::vector<std::unique_ptr<Game_object>> scene_objects;
};

#endif
