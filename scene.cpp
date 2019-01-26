#include "scene.h"

void Scene::update()
{
    for (auto & object : scene_objects) {
        object->update();
    }
}

void Scene::draw(sdlxx::Sdl_renderer & renderer)
{
    for (auto & object : scene_objects) {
        object->draw(renderer);
    }
}
