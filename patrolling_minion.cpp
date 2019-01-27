#include "patrolling_minion.h"

Patrolling_Minion::Patrolling_Minion(sdlxx::Sdl_renderer& renderer, int x_pos, int y_pos)
    : Mover{renderer,
            50,
            50,
            x_pos,
            y_pos,
            "resources/minion.bmp"}
{
    isPlayer = false;
    isVillain = true;
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