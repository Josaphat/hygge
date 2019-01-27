#ifndef SCENEIMPORTER_H
#define SCENEIMPORTER_H

#include <SDL.h>
#include <map>
#include <string>
#include <vector>

#include "../platforming_scene.h"

namespace sdlxx {

class SceneImporter {
public:
    enum class Symbol : char {
        Dot = '.',
        X = 'X',
        R = 'R',
        G = 'G',
        B = 'B',
        M = 'M',
    };

    SceneImporter(Sdl_renderer& ren);
    ~SceneImporter();

    Platforming_scene load(std::string path);

private:
    Sdl_renderer& renderer;
    std::map<Symbol, std::vector<SDL_Rect>> objects;
};
}  // namespace sdlxx
#endif  // !SCENEIMPORTER_H
