#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include "include/sdlxx.h"
#include "vec2.h"
#include "asteroid_scene.h"
#include "input_map.h"
#include "screen_config.h"

using namespace std::chrono_literals;
using namespace std::string_literals;

// Global Input Map
Input_map input_state;

int main(int argc, char* argv[])
{
    using namespace sdlxx;
    const auto sdl_sys = Sdl_system(SDL_INIT_VIDEO);

    // The Window is the operating system thing that contains our drawing space.
    // It's the thing with the X in the corner and the frame thing around it.
    // You may know it as "chrome".
    auto window = Sdl_window("hello, world", 100, 100, window_height,
                             window_width, SDL_WINDOW_SHOWN);

    // The renderer lets us create the pixels in memory
    auto ren = Sdl_renderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    auto image_path = "resources/"s + "ship.bmp"s;
    auto tex = Sdl_texture{image_path, ren};

    Asteroid_scene asteroid_scene {ren};
    auto & current_scene = asteroid_scene;

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
                    input_state.accelerate = true;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    input_state.rotate_left = true;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    // nothing
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    input_state.rotate_right = true;
                    break;
                }
            }
            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_w:
                case SDLK_UP:
                    input_state.accelerate = false;
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    input_state.rotate_left = false;
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    input_state.rotate_right = false;
                    break;
                }
            }

            // If the mouse is clicked
            if (e.type == SDL_MOUSEBUTTONDOWN) { quit = true; }
        }

        while (lag >= millis_per_update) {
            // Update
            current_scene.update();

            lag -= millis_per_update;
        }

        // Render
        ren.clear();
        current_scene.draw(ren);
        ren.present();
    }

    return 0;
}
