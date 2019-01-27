#include "patrolling_minion.h"
#include "input_map.h"
#include "screen_config.h"

Patrolling_Minion::Patrolling_Minion(sdlxx::Sdl_renderer& renderer, int x_pos, int y_pos)
    : Game_object{height,
				  width,
				  {static_cast<double>(x_pos), static_cast<double>(y_pos)},
				  {0, 0},
				  true},
	texture{"resources/minion.bmp", renderer }
{
    isPlayer = false;
    isVillain = true;
}
void Patrolling_Minion::update()
{
	// if we're going to run off the scene switch directions
	if (position.x >= window_width - 45) {
		move_right = false;
	}
	if (position.x <= 25) {
		move_right = true;
	}

	velocity.x = 0;
	if (move_right) { velocity.x += move_speed; }
	else {
		velocity.x -= move_speed;
	}

	velocity.y += gravity;
}

void Patrolling_Minion::draw(sdlxx::Sdl_renderer& renderer)
{
	position.y += velocity.y;
	position.x += velocity.x;
	renderer.draw_rect(position.x, position.y, width, height, 0, 0, 255);
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = width;
	rect.h = height;
	SDL_RendererFlip flip{ SDL_FLIP_NONE };
	if (move_right) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0.0, NULL, flip);
}
void Patrolling_Minion::collide(Game_object& rhs)
{
	bool on_top = false;
	if (rhs.isPlatform && velocity.y > 0) {
		// We're falling
		auto overlap_y = (position.y + height + velocity.y) - rhs.position.y;
		// Check if the bottommost border is already past the objects topmost border
		bool past_border;
		if (((position.y + height - velocity.y) - rhs.position.y) > 0) {
			past_border = true;
		}
		else {
			past_border = false;
		}
		if (overlap_y > 0 && past_border == false) {
			// We're starting to go through a platform.
			velocity.y = 0;
			position.y = rhs.position.y - height;
			on_top = true;
		}
	}

	if (rhs.isPlatform && velocity.x < 0 && on_top == true) {
		// We're moving to the left
		// Check if the leftmost border is already past the objects leftmost border
		bool past_border;
		if ((position.x - rhs.position.x) < 0) {
			past_border = true;
		}
		else {
			past_border = false;
		}
		if (past_border == true) {
			move_right = true;
		}
	}

	if (rhs.isPlatform && velocity.x > 0 && on_top == true) {
		// We're moving to the right
        // Check if the rightmost border is already past the objects leftmost border
		bool past_border;
		if (((position.x + width) - (rhs.position.x + rhs.width)) > 0) {
			past_border = true;
		}
		else {
			past_border = false;
		}
		if (past_border == true) {
			move_right = false;
		}
	}

	// If we're moving left or right and we hit a barrier move back to the last position of the x coordinate
	if (rhs.isPlatform && velocity.x > 0 && on_top == false) {
		// We're moving to the right
		// Overlap into the object
		auto overlap_x = (position.x + width + velocity.x) - rhs.position.x;
		// Check if the leftmost border is already past the objects leftmost border
		bool past_border;
		if ((position.x - rhs.position.x) > 0) {
			past_border = true;
		}
		else {
			past_border = false;
		}
		if (overlap_x > 0 && past_border == false) {
			velocity.x = 0;
			position.x = rhs.position.x - width;
			move_right = false;
		}
	}
	else if (rhs.isPlatform && velocity.x < 0 && on_top == false) {
		// We're moving to the left
		auto overlap_x = (position.x + velocity.x) - (rhs.position.x + rhs.width);
		// Check if the rightmost border is already past the objects leftmost border
		bool past_border;
		if (((position.x + width) - (rhs.position.x + rhs.width)) < 0) {
			past_border = true;
		}
		else {
			past_border = false;
		}
		if (overlap_x < 0 && past_border == false) {
			velocity.x = 0;
			position.x = rhs.position.x + rhs.width;
			move_right = true;
		}
	}
}