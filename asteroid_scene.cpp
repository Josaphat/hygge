#include "asteroid_scene.h"
#include "ship.h"

Asteroid_scene::Asteroid_scene(sdlxx::Sdl_renderer & renderer)
{
    scene_objects.emplace_back(std::make_unique<Ship>(renderer));
}
