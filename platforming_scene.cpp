#include "platforming_scene.h"
#include "platform.h"
#include "goal.h"
#include "player.h"
#include "pupper.h"
#include "screen_config.h"
#include "home_scene.h"

extern Scene * current_scene;
extern std::unique_ptr<Home_scene> home;

Platforming_scene::Platforming_scene(sdlxx::Sdl_renderer& renderer) : _renderer(renderer)
{

}

void Platforming_scene::update()
{
    Player* player = nullptr;
    Pupper* pupper = nullptr;
    Goal* mailbox = nullptr;
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
    for (auto iter = scene_objects.begin(); iter != scene_objects.end();) {
        if ((**iter).should_be_destroyed() == true)
            iter = scene_objects.erase(iter);
        else
            ++iter;
    }

    if (player->collides_with(*mailbox)) {
        if (pupper->isHeld()) {
            current_scene = home.get();
        }
    }
}
