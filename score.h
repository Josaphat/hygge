#ifndef SCORE_H
#define SCORE_H

#include <string>

#include "include/sdlxx.h"

using namespace sdlxx;

class Score {
public:
    Score() {}
    ~Score() {}
    static Score& sharedInstance() {
        static Score instance;
        return instance;
    }
    void increment() {
        ++score;
    }
    void set(int newScore) {
        score = newScore;
    }
    int get() {
        return score;
    }

    void draw(Sdl_renderer& renderer) {
        // Draw the score
        auto texture = Sdl_texture{ "resources/numbers.bmp", renderer };
        std::string scoreStr = std::to_string(Score::sharedInstance().get());
        int x = 50;
        int y = 50;
        for (char& c : scoreStr) {
            int i = c - '0';
            SDL_Rect clip;
            clip.x = 63 * i;
            clip.y = 0;
            clip.w = 63;
            clip.h = 64;
            renderer.copy(texture, x, y, &clip);
            x += 63;
        }
    }
private:
    int score{ 0 };
};

#endif