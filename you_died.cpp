#include "you_died.h"
#include "home_scene.h"
#include <chrono>

extern decltype(std::chrono::high_resolution_clock::now()) die_time;
extern Scene * current_scene;
extern std::unique_ptr<Home_scene> home;

You_died::You_died(sdlxx::Sdl_renderer& renderer)
    : _renderer(renderer), _tex{"resources/you_died.bmp", _renderer}
{
}

void You_died::update()
{
    using namespace std::chrono_literals;

    if (std::chrono::high_resolution_clock::now() - die_time > 5s) {
        home->player_died();
        current_scene = home.get();
    }
}
void You_died::draw(sdlxx::Sdl_renderer& renderer)
{
    renderer.copy(_tex, 0, 0);
}
