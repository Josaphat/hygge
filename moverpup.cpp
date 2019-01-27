#include "moverpup.h"

MoverPup::MoverPup(sdlxx::Sdl_renderer& renderer, int x_pos, int y_pos)
    : Mover{renderer,
            35,
            50,
            x_pos,
            y_pos,
            "resources/pupper.bmp" }
{
    isPlayer = false;
    isVillain = false;
    isPupper = true;
    move_speed = rand() % 9 + 2;
    air_move_speed = move_speed - 1;
    gravity = rand() % 5 + 1;

    move_right = rand() % 2;
}

void MoverPup::update()
{
    int jumpchance = rand() % 100;
    if ((velocity.y == 0) && (jumpchance < 1)) {
        velocity.y -= gravity * 10 - 1; // -1 so the puppers can't doublejump
    }
    Mover::update();
}

void MoverPup::collide(Game_object& rhs)
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

            // They're no longer jumping
            //jumping = false;
            //double_jump = false;
            velocity.y = 0;
            position.y = rhs.position.y - height;
            on_top = true;
        }
    }

    // If we're moving left or right and we hit a barrier move back to the last position of the x coordinate
    if (rhs.isPlatform && move_speed > 0 && on_top == false) {
        // We're moving to the right
        // Overlap into the object
        auto overlap_x = (position.x + width + move_speed) - rhs.position.x;
        // Check if the leftmost border is already past the objects leftmost border
        bool past_border;
        if ((position.x - rhs.position.x) > 0) {
            past_border = true;
        }
        else {
            past_border = false;
        }
        if (overlap_x > 0 && past_border == false) {
            position.x = rhs.position.x - width;
            move_right = !move_right;
        }
    }
    else if (rhs.isPlatform && move_speed < 0 && on_top == false) {
        // We're moving to the left
        auto overlap_x = (position.x + move_speed) - (rhs.position.x + rhs.width);
        // Check if the rightmost border is already past the objects leftmost border
        bool past_border;
        if (((position.x + width) - (rhs.position.x + rhs.width)) < 0) {
            past_border = true;
        }
        else {
            past_border = false;
        }
        if (overlap_x < 0 && past_border == false) {
            position.x = rhs.position.x + rhs.width;
            move_right = !move_right;
        }
    }
}