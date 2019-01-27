#include "player.h"
#include "input_map.h"
#include "screen_config.h"
#include "score.h"

Player::Player(sdlxx::Sdl_renderer& renderer)
    : Game_object{/*height*/ 75,
                  /*width*/ 50,
                  {0, static_cast<double>(window_height - 75)},
                  {0, 0}},
      texture{"resources/hyggens.bmp", renderer}
{
    isPlayer = true;
    isVillain = false;
}

void Player::update()
{

    if (input_state.move_left) {
		velocity.x = -move_speed;
	}
    if (input_state.move_right) {
		velocity.x = move_speed;
	}
	if (!input_state.move_right && !input_state.move_left) {
		velocity.x = 0;
	}
	//position.x += velocity.x;

    if (input_state.jump && !jumping) {
        jumping = true;
        velocity.y = -30;
        jump_frame = 0;
        ready_for_double_jump = false;
    }
    if (!ready_for_double_jump && jumping && !input_state.jump) {
        ready_for_double_jump = true;
    }
    if (ready_for_double_jump && input_state.jump && !double_jump) {
        double_jump = true;
        velocity.y = -30;
        jump_frame = 0;
    }

    velocity.y += gravity;
    //position.y += velocity.y;

    if (jumping) {
        ++jump_frame;

        if (position.y >= window_height - height) {
            position.y = window_height - height;
            jumping = false;
            double_jump = false;
        }
    }
}

void Player::draw(sdlxx::Sdl_renderer& renderer)
{
    position.x += velocity.x;
    position.y += velocity.y;
    renderer.draw_rect(position.x, position.y, width, height, 0, 255, 0);
    renderer.copy(texture, int(position.x), int(position.y));
}

void Player::collide(Game_object& rhs)
{

    if (rhs.isVillain) {
        rhs.set_to_destroy();
        Score::sharedInstance().increment();
    }

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

			// They're no longer jumping
			jumping = false;
			double_jump = false;
			velocity.y = 0;
			position.y = rhs.position.y - height;
			on_top = true;
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
		}
	}


}
