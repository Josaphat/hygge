#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include "home_scene.h"
#include "sceneimporter.h"
#include "include/sdlxx.h"
#include "input_map.h"
#include "platforming_scene.h"
#include "you_died.h"
#include "screen_config.h"
#include "tutorial_scene.h"
#include "vec2.h"

using namespace std::chrono_literals;
using namespace std::string_literals;

// Global Input Map
Input_map input_state;

std::unique_ptr<Tutorial_scene> tutorial;
std::unique_ptr<Home_scene> home;
std::unique_ptr<You_died> you_died;

std::vector<Platforming_scene> scenes;
std::vector<Platforming_scene>::iterator platscene_iter;
Scene * current_scene;

int main(int argc, char* argv[])
{
    using namespace sdlxx;
    const auto sdl_sys = Sdl_system(SDL_INIT_VIDEO);

    // The Window is the operating system thing that contains our drawing space.
    // It's the thing with the X in the corner and the frame thing around it.
    // You may know it as "chrome".
    auto window = Sdl_window("hello, world", 0, 0, window_width, window_height,
                             SDL_WINDOW_SHOWN);

    // The renderer lets us create the pixels in memory
    auto ren = Sdl_renderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Sdl_texture background{"resources/Snow_covered_pine.bmp", ren};

    SceneImporter importer{ren};
    tutorial = std::make_unique<Tutorial_scene>(
        importer.load<Tutorial_scene>("scenes/tutorial_scene.txt"s));
    home =
        std::make_unique<Home_scene>(importer.load<Home_scene>("scenes/sceneHouse.txt"s));
    you_died = std::make_unique<You_died>(ren);
    for (auto i = 0; i < 4; ++i) {
        scenes.emplace_back(
            importer.load<Platforming_scene>("scenes/scene"s + std::to_string(i) + ".txt"s));
    }

    current_scene = tutorial.get();
    platscene_iter = scenes.begin();

    // Main Loop
    constexpr auto millis_per_update = 16ms;  // about 60FPS
    auto previous = std::chrono::high_resolution_clock::now();
    auto lag = previous - previous;

    bool quit{false};
    while (!quit) {
        auto current = std::chrono::high_resolution_clock::now();
        auto elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // Process input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // If the window gets closed
            if (e.type == SDL_QUIT) { quit = true; }

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    default:
                        break;
                    case SDLK_q:
                        quit = true;
                        break;

                    case SDLK_w:
                    case SDLK_UP:
                        input_state.jump = true;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        // nothing
                        break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        input_state.move_left = true;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        input_state.move_right = true;
                        break;
                }
            }
            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_UP:
                        input_state.jump = false;
                        break;
                    case SDLK_s:
                    case SDLK_DOWN:
                        break;
                    case SDLK_a:
                    case SDLK_LEFT:
                        input_state.move_left = false;
                        break;
                    case SDLK_d:
                    case SDLK_RIGHT:
                        input_state.move_right = false;
                        break;
                }
            }

            // If the mouse is clicked
            if (e.type == SDL_MOUSEBUTTONDOWN) { quit = true; }
        }

        while (lag >= millis_per_update) {
            current_scene->update();
            lag -= millis_per_update;
        }

        // Render
        ren.clear();
        ren.copy(background, 0, 0);
        current_scene->draw(ren);
        ren.present();
    }

    return 0;
}
