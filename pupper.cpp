#include "pupper.h"
#include "platforming_scene.h"
#include "screen_config.h"

Pupper::Pupper(sdlxx::Sdl_renderer& renderer, int x, int y)
    : Game_object{/*height*/ 35,
                  /*width*/ 50,
                  {static_cast<double>(x), static_cast<double>(y)},
                  {0, 0}},
      texture{"resources/pupper.bmp", renderer}
{
}

extern std::vector<Platforming_scene>::iterator current_scene;

void Pupper::update() {
    if (position.x > window_width) {
        ++current_scene;
    }
}

void Pupper::collide(Game_object& other)
{
    if (other.isPlayer) {
        held = true;
        position.x = other.position.x + 10;
        position.y = other.position.y + 20;
    }
}

void Pupper::draw(sdlxx::Sdl_renderer& renderer)
{
    renderer.copy(texture, int(position.x), int(position.y));
}
