#include "platforming_scene.h"
#include <chrono>
#include "home_scene.h"
#include "platform.h"
#include "screen_config.h"
#include "you_died.h"
#include "score.h"

extern Scene* current_scene;
extern std::unique_ptr<You_died> you_died;
extern std::unique_ptr<Home_scene> home;

decltype(std::chrono::high_resolution_clock::now()) die_time;

Platforming_scene::Platforming_scene(sdlxx::Sdl_renderer& renderer)
    : _renderer(renderer)
{
}

void Platforming_scene::update()
{
    if (player == nullptr) {
        for (auto& object : scene_objects) {
            if (object->isPlayer) {
                player = dynamic_cast<Player*>(object.get());
                player_spawn.x = player->position.x;
                player_spawn.y = player->position.y;
            }
            if (object->isPupper) {
                pupper = dynamic_cast<Pupper*>(object.get());
                pup_spawn = pupper->position;
            }
            if (object->isGoal) { mailbox = dynamic_cast<Goal*>(object.get()); }
        }
    }

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

    if (player->position.y > window_height) {
        // Dead!
        die_time = std::chrono::high_resolution_clock::now();
        current_scene = you_died.get();
        player->position.x = player_spawn.x;
        player->position.y = player_spawn.y;
        pupper->position = pup_spawn;
        pupper->held = false;
    }

    if (player->collides_with(*mailbox)) {
        if (pupper->isHeld()) {
            player->position.x = player_spawn.x;
            player->position.y = player_spawn.y;
            pupper->position = pup_spawn;
            pupper->held = false;
            current_scene = home.get();
            Score::sharedInstance().increment();
        }
    }
}
