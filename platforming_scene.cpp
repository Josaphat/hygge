#include "platforming_scene.h"
#include "minion.h"
#include "platform.h"
#include "player.h"
#include "screen_config.h"

Platforming_scene::Platforming_scene(sdlxx::Sdl_renderer& renderer)
{

}

void Platforming_scene::update()
{
    for (auto& object : scene_objects) { object->update(); }

    for (auto a = scene_objects.begin(); a < scene_objects.end(); ++a) {
        for (auto b = scene_objects.begin(); b < scene_objects.end(); ++b) {
            // Don't collide with yourself
            if (a == b) { continue; }

            if ((**a).collides_with(**b)) { (**a).collide(**b); }
        }
    }
    for (auto iter = scene_objects.begin(); iter != scene_objects.end();) {
        if ((**iter).should_be_destroyed() == true)
            iter = scene_objects.erase(iter);
        else
            ++iter;
    }
}
