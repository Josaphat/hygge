#include "platforming_scene.h"
#include "player.h"

Platforming_scene::Platforming_scene(sdlxx::Sdl_renderer & renderer)
{
    scene_objects.emplace_back(std::make_unique<Player>());
}
