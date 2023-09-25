/**
 * @file player.h
 */
#ifndef __PLAYER_H
#define __PLAYER_H

#include <libdragon.h>
#include <math.h>
#include "../utils.h"
#include "actor.h"

typedef struct player_t {
    actor_t actor;
} player_t;

typedef struct controller_state_t {
    bool A;
    bool B;
    bool C_up;
    bool C_down;
    bool C_left;
    bool C_right;
    unsigned int data;
    bool down;
    bool L;
    bool left;
    bool R;
    bool right;
    bool start;
    bool up;
    unsigned int x;
    unsigned int y;
    unsigned int Z;
} controller_state_t;

void player_init(player_t *player, sprite_t *sprite, Vector2 position);

void player_draw(player_t *player, uint32_t animcounter);

void player_handle_controller(player_t *player, controller_state_t *controller_state);

#endif /* __PLAYER_H */
