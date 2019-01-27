#include "scene.h"
#include "score.h"
#include "include/sdlxx.h"

using namespace sdlxx;

void Scene::update()
{
    for (auto& object : scene_objects) { object->update(); }
}

void Scene::draw(sdlxx::Sdl_renderer& renderer)
{
    for (auto& object : scene_objects) { object->draw(renderer); }

    printf("Drawing, score is currently: %d\n", Score::sharedInstance().get());
    Score::sharedInstance().draw(renderer);
}

void Scene::addObject(std::unique_ptr<Game_object> object)
{
    scene_objects.emplace_back(std::move(object));
}

void Scene::addObject(std::unique_ptr<Game_object> object, int)
{
    scene_objects.insert(scene_objects.begin(), std::move(object));
}
