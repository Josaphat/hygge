#ifndef HYGGE_SCENE_H
#define HYGGE_SCENE_H

#include <memory>
#include <vector>
#include "game_object.h"
#include "include/sdlxx.h"

class Scene {
public:
    virtual void update();
    virtual void draw(sdlxx::Sdl_renderer& renderer);
    void addObject(std::unique_ptr<Game_object> object);
    void addObject(std::unique_ptr<Game_object> object, int);

protected:
    std::vector<std::unique_ptr<Game_object>> scene_objects;
};

#endif
