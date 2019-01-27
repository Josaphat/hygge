#include "home_scene.h"
#include "player.h"
#include "platforming_scene.h"
#include "score.h"
#include "moverpup.h"

extern Scene * current_scene;
extern std::vector<Platforming_scene>::iterator platscene_iter;

static double starting_position_x = 0;
static double starting_position_y = 0;
Home_scene::Home_scene(sdlxx::Sdl_renderer& renderer) : renderer{renderer} {
}

void Home_scene::player_died()
{
    player_was_dead = true;
}

void Home_scene::removePupper() {
    std::vector<std::unique_ptr<Game_object>>::iterator it;
    for (it = scene_objects.begin(); it < scene_objects.end(); ++it) {
        if ((*it)->isPupper) {
            scene_objects.erase(it);
            --pups;
            break;
        }
    }
}

void Home_scene::update()
{
    Player* player = nullptr;
    if (player == nullptr) {
        for (auto& object : scene_objects) {
            if (object->isPlayer) {
                player = dynamic_cast<Player*>(object.get());
                if (starting_position_x == 0) {
                    starting_position_x = player->position.x;
                    starting_position_y = player->position.y;
                }
            }
        }
    }
    if (pups < Score::sharedInstance().get()) {
        addObject(std::make_unique<MoverPup>(
            renderer, player->position.x, player->position.y + 100));
        ++pups;
    }
    if (pups > Score::sharedInstance().get()) {
        removePupper();
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

    if (player->position.x < 0) {
        if (player_was_dead) {
            --platscene_iter;
            player_was_dead = false;
        }
        current_scene = &(*platscene_iter);
        ++platscene_iter;

        player->position.x = starting_position_x;
        player->position.y = starting_position_y;
    }
}
