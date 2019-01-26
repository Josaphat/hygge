#ifndef SCENEIMPORTER_H
#define SCENEIMPORTER_H

#include <SDL.h>
#include <string>
#include <map>
#include <vector>

#include "../scene.h"

namespace sdlxx {

    class SceneImporter {
    public:
        enum class Symbol : char {
            Dot = '.',
            X = 'X',
            R = 'R',
            G = 'G',
        };

        SceneImporter(Sdl_renderer & ren);
        ~SceneImporter();

        Scene load(std::string path);
    private:
        Sdl_renderer & renderer;
        std::map<Symbol, std::vector<SDL_Rect>> objects;
    };
}
#endif // !SCENEIMPORTER_H
