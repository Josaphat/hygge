#include "home_scene.h"
#include "player.h"
#include "pupper.h"
#include "platforming_scene.h"
#include "score.h"
#include "moverpup.h"

extern Scene * current_scene;
extern std::vector<Platforming_scene>::iterator platscene_iter;

Home_scene::Home_scene(sdlxx::Sdl_renderer& renderer) : renderer{renderer} {}

void Home_scene::update()
{
    if (pups < Score::sharedInstance().get()) {
        addObject(std::make_unique<MoverPup>(renderer, 50, 50));
        ++pups;
    }
    Player* player = nullptr;
    Pupper* pupper = nullptr;
    if (player == nullptr) {
        for (auto& object : scene_objects) {
            if (object->isPlayer) {
                player = dynamic_cast<Player*>(object.get());
            }
            if (object->isPupper) {
                pupper = dynamic_cast<Pupper*>(object.get());
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

    if (player->position.x < -player->width) {
        player->position.x = 10;
        current_scene = &(*platscene_iter);
        ++platscene_iter;
    }
}
