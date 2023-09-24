/**
 * @file player.h
 */
#ifndef __NPC_H
#define __NPC_H

#include <libdragon.h>
#include <math.h>
#include "../utils.h"
#include "actor.h"

typedef enum npc_action_t
{
    Idle,
    Spin,
    Pace,
    Path,
} npc_action_t;

typedef struct npc_path_t
{
    Vector2 path[10];
    uint8_t path_length;
    uint8_t path_index;
    bool path_loop;
} npc_path_t;


typedef struct npc_t {
    actor_t actor;
    npc_action_t action;
    uint8_t steps;
    uint8_t spin_rate;
    uint8_t pace_steps;
    uint8_t path_rate;
    npc_path_t path;
    bool path_direction; // false for forward, true for backward
} npc_t;

void npc_init(npc_t *npc, sprite_t *sprite, Vector2 position, direction_t direction, npc_action_t action, uint8_t spin_rate, uint8_t pace_steps);

void npc_draw(npc_t *npc, uint32_t animcounter);

void npc_update(npc_t *player, uint32_t animcounter);

void npc_update_movement(npc_t *npc);

#endif /* __NPC_H */
