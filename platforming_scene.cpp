#include "platforming_scene.h"
#include "platform.h"
#include "player.h"
#include "screen_config.h"

Platforming_scene::Platforming_scene(sdlxx::Sdl_renderer & renderer)
{
    scene_objects.emplace_back(std::make_unique<Player>());

    scene_objects.emplace_back(std::make_unique<Platform>((window_width / 2) - 100 - 250,
                                                          window_height - 150,
                                                          250, 10));

    scene_objects.emplace_back(std::make_unique<Platform>((window_width / 2) - 50,
                                                          window_height - 200,
                                                          250, 10));
}
