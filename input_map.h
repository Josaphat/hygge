#ifndef HYGGE_INPUT_MAP_H
#define HYGGE_INPUT_MAP_H

struct Input_map {
    bool rotate_left = false;
    bool rotate_right = false;
    bool accelerate = false;
};

// Global Input state
extern Input_map input_state;

#endif
