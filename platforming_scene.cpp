#include "platforming_scene.h"
#include "platform.h"
#include "player.h"
#include "minion.h"
#include "screen_config.h"

Platforming_scene::Platforming_scene(sdlxx::Sdl_renderer & renderer)
{
    //scene_objects.emplace_back(std::make_unique<Player>(renderer));
    scene_objects.emplace_back(std::make_unique<Minion>(renderer));

	scene_objects.emplace_back(std::make_unique<Minion>(renderer, 100, 500));
	scene_objects.emplace_back(std::make_unique<Minion>(renderer, 200, 500));
	scene_objects.emplace_back(std::make_unique<Minion>(renderer, 500, 500));
	scene_objects.emplace_back(std::make_unique<Minion>(renderer, 923, 500));

    //scene_objects.emplace_back(std::make_unique<Platform>(0, window_height - 10,
    //                                                      window_width,
    //                                                      window_height));
    //scene_objects.emplace_back(std::make_unique<Platform>((window_width / 2) - 100 - 250,
    //                                                      window_height - 150,
    //                                                      250, 10));

    //scene_objects.emplace_back(std::make_unique<Platform>((window_width / 2),
    //                                                      window_height - 200,
    //                                                      250, 10));
}

void Platforming_scene::update()
{
    for (auto & object : scene_objects) {
        object->update();
    }

    for (auto a = scene_objects.begin(); a < scene_objects.end(); ++a) {
        for (auto b = scene_objects.begin(); b < scene_objects.end(); ++b) {
            // Don't collide with yourself
            if (a == b) { continue; }

            if ((**a).collides_with(**b)) {
                (**a).collide(**b);
            }
        }
    }
	for (auto iter = scene_objects.begin(); iter != scene_objects.end(); ) {
		if ((**iter).should_be_destroyed() == true)
			iter = scene_objects.erase(iter);
		else
			++iter;
	}
}
