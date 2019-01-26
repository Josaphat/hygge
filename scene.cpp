#include "scene.h"

void Scene::update()
{
    for (auto& object : scene_objects) { object->update(); }
}

void Scene::draw(sdlxx::Sdl_renderer& renderer)
{
    for (auto& object : scene_objects) { object->draw(renderer); }
}

void Scene::addObject(std::unique_ptr<Game_object> object)
{
    scene_objects.emplace_back(std::move(object));
}
