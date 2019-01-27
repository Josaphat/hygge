#include "include/sceneimporter.h"
#include "include/sdlxx.h"
#include "platform.h"
#include "platforming_scene.h"
#include "player.h"
#include "pupper.h"
#include "minion.h"

#include <fstream>
#include <iostream>

using namespace sdlxx;
using namespace std;

SceneImporter::SceneImporter(Sdl_renderer& ren) : renderer(ren) {}

SceneImporter::~SceneImporter() {}

Platforming_scene SceneImporter::load(string path)
{
    Platforming_scene scene{renderer};
    // read in BMP file or some **** like that
    ifstream file(path);
    if (file.is_open()) {
        string line;
        // make an SDL_Surface outta it
        // check out dem pixels
        // turn dem pixels into The Scene

        // for each pixel
        int x = -1;
        int y = -1;
        while (getline(file, line)) {
            ++y;
            x = -1;
            for (char& c : line) {
                ++x;
                // if blank:
                Symbol sym = static_cast<Symbol>(c);
                if (sym == Symbol::Dot) {
                    // skip
                    continue;
                }
                // otherwise:
                // for each object of pixel's color:
                if (objects.count(sym) < 1) {
                    objects.emplace(sym, std::vector<SDL_Rect>());
                }
                bool didUpdate = false;
                for (int i = 0; i < objects[sym].size(); ++i) {
                    SDL_Rect rect = objects[sym][i];

                    bool withinX = (rect.x <= x) && ((rect.x + rect.w) > x);
                    bool withinY = (rect.y <= y) && ((rect.y + rect.h) > y);
                    // if pixel within already-recorded bounds
                    if (withinX && withinY) {
                        // skip
                        didUpdate = true;
                        break;
                    }

                    bool adjacentX = (rect.y == y) && ((rect.x + rect.w) == x);
                    bool adjacentY = (rect.x == x) && ((rect.y + rect.h) == y);
                    // if pixel adjacent to object's recorded bounds:
                    // update object's recorded bounds to include pixel
                    if (adjacentX) {
                        ++objects[sym][i].w;
                        didUpdate = true;
                        break;
                    }
                    if (adjacentY) {
                        ++objects[sym][i].h;

                        didUpdate = true;
                        break;
                    }
                }
                if (!didUpdate) {
                    // create new object of pixel's color, with bounds including
                    // the pixel
                    SDL_Rect newRect;
                    newRect.x = x;
                    newRect.y = y;
                    newRect.w = 1;
                    newRect.h = 1;
                    objects[sym].push_back(newRect);
                }
            }
        }
        file.close();
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            Symbol sym = it->first;
            std::vector<SDL_Rect> vec = it->second;
            for (SDL_Rect rect : vec) {
                printf("%cRect: x%d y%d w%d h%d\n", char(sym), rect.x, rect.y,
                       rect.w, rect.h);
                rect.x *= 10;
                rect.y *= 10;
                rect.w *= 10;
                rect.h *= 10;
                switch (sym) {
                    case Symbol::G:
                        scene.addObject(std::make_unique<Player>(renderer), 0);
                        break;
                    case Symbol::R:
                        scene.addObject(std::make_unique<Platform>(
                            rect.x, rect.y, rect.w, rect.h));
                        break;
                    case Symbol::X:
                        scene.addObject(std::make_unique<Platform>(
                            rect.x, rect.y, rect.w, rect.h));
                        break;
                    case Symbol::B:
                        scene.addObject(
                            std::make_unique<Pupper>(renderer, rect.x, rect.y));
                        break;
                    case Symbol::M:
                        scene.addObject(std::make_unique<Minion>(renderer, rect.x, rect.y));
                        break;
                    default:
                        break;
                }
            }
        }
    }

    return scene;
}
