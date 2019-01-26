#ifndef HYGGE_GAME_OBJECT_H
#define HYGGE_GAME_OBJECT_H

#include "include/sdlxx.h"
#include "vec2.h"
#include <cmath>

class Game_object {
public:
    Game_object(int height, int width, Vec2 position, Vec2 velocity, bool can_be_destroyed = false)
		: height{ height }, width{ width }, position{ position }, velocity{ velocity }, can_be_destroyed{can_be_destroyed}
    {
    }

    virtual void update() = 0;
    virtual void draw(sdlxx::Sdl_renderer & renderer) = 0;

    bool collides_with(const Game_object & rhs) {
        auto lhs_center = Vec2{position.x + (width / 2.0), position.y + (height / 2.0)};
        auto rhs_center = Vec2{rhs.position.x + (rhs.width / 2.0), rhs.position.y + (rhs.height / 2.0)};
        if (std::abs(lhs_center.x - rhs_center.x) > (width / 2.0) + (rhs.width / 2.0)) {
            return false;
        }
        if (std::abs(lhs_center.y - rhs_center.y) > (height / 2.0) + (rhs.height / 2.0)) {
            return false;
        }
        return true;
    }

    virtual void collide(Game_object & other){}

	void set_to_destroy()
	{
		if (can_be_destroyed) {
			destroy = true;
		}
	}

	bool should_be_destroyed()
	{
		return destroy;
	}

	const bool can_be_destroyed;
    const int height;
    const int width;
    Vec2 position;
    Vec2 velocity;
	bool destroy = false;
};

#endif
