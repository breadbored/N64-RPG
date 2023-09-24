/**
 * @file actor.h
 */
#ifndef __ACTOR_H
#define __ACTOR_H

#include <libdragon.h>
#include <math.h>
#include "../utils.h"

typedef enum direction_t
{
    Down,
    Up,
    Left,
    Right
} direction_t;

typedef struct actor_t {
    Vector2 position;

    // Movement Animation Related
    bool moving;
    uint8_t movementCounter;
    uint8_t movementDelay;
    direction_t direction;
    Vector2 fromPosition;
    Vector2 toPosition;

    sprite_t *sprite;
} actor_t;

void actor_init(actor_t *actor, sprite_t *sprite, Vector2 position);

int actor_frame(actor_t *actor, uint32_t *animcounter);

Vector2 get_screen_coordinates(Vector2 position);

void actor_draw(actor_t *actor, uint32_t *animcounter);

bool will_collide(Vector2 toPosition);

#endif /* __ACTOR_H */
