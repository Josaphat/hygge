#include "tutorial_scene.h"
#include "goal.h"
#include "player.h"
#include "pupper.h"
#include "screen_config.h"
#include "home_scene.h"

extern Scene * current_scene;
extern std::unique_ptr<Home_scene> home;

Tutorial_scene::Tutorial_scene(sdlxx::Sdl_renderer& /*renderer*/) {}

void Tutorial_scene::update()
{
    Player* player = nullptr;
    Pupper* pupper = nullptr;
    Goal * mailbox = nullptr;
    if (player == nullptr) {
        for (auto& object : scene_objects) {
            if (object->isPlayer) {
                player = dynamic_cast<Player*>(object.get());
            }
            if (object->isPupper) {
                pupper = dynamic_cast<Pupper*>(object.get());
            }
            if (object->isGoal) {
                mailbox = dynamic_cast<Goal*>(object.get());
            }
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

    for (auto it = scene_objects.begin(); it != scene_objects.end();) {
        if ((**it).should_be_destroyed()) { it = scene_objects.erase(it); }
        else {
            ++it;
        }
    }

    // If the player brings the pupper to the mailbox
    if (player->collides_with(*mailbox) ) {
        if (pupper->isHeld()) {
            scene_objects.clear();
            current_scene = home.get();
        }
    }
}
