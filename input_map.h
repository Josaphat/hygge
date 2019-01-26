#ifndef HYGGE_INPUT_MAP_H
#define HYGGE_INPUT_MAP_H

struct Input_map {
    bool move_left = false;
    bool move_right = false;
};

// Global Input state
extern Input_map input_state;

#endif
