#include <libdragon.h>
#include <math.h>
#include "../globals.h"
#include "../utils.h"
#include "actor.h"
#include "npc.h"

void npc_init(npc_t *npc, sprite_t *sprite, Vector2 position, direction_t direction, npc_action_t action, uint8_t spin_rate, uint8_t pace_steps)
{
    actor_init(&(npc->actor), sprite, position);
    npc->actor.direction = direction;
    npc->action = action;
    npc->spin_rate = spin_rate;
    npc->pace_steps = pace_steps;
    npc->steps = 0;
}

void npc_draw(npc_t *npc, uint32_t animcounter)
{
    actor_draw(&(npc->actor), &animcounter);
}

void npc_update(npc_t *npc, uint32_t animcounter)
{
    npc_update_movement(npc);
}

void npc_update_movement(npc_t *npc) {
    // Do not render if the actor is outside the screen
    Vector2 screen_coordinates = get_screen_coordinates(npc->actor.position);
    if (screen_coordinates.x < -128 || screen_coordinates.x > screen_size.x + 128 || screen_coordinates.y < -128 || screen_coordinates.y > screen_size.y + 128) {
        return;
    }

    switch (npc->action) {
        case Idle:
            break;
        case Spin:
            if (npc->actor.movementCounter > npc->spin_rate) {
                switch (npc->actor.direction) {
                    case Down:
                        npc->actor.direction = Right;
                        break;
                    case Up:
                        npc->actor.direction = Left;
                        break;
                    case Left:
                        npc->actor.direction = Down;
                        break;
                    case Right:
                        npc->actor.direction = Up;
                        break;
                }
                npc->actor.movementCounter = 0;
            } else {
                npc->actor.movementCounter++;
            }
            break;
        case Pace:
            if (npc->steps > npc->pace_steps) {
                switch (npc->actor.direction) {
                    case Down:
                        npc->actor.direction = Up;
                        break;
                    case Up:
                        npc->actor.direction = Down;
                        break;
                    case Left:
                        npc->actor.direction = Right;
                        break;
                    case Right:
                        npc->actor.direction = Left;
                        break;
                }
                npc->steps = 0;
            }
            if (!npc->actor.moving) {
                if( npc->actor.direction == Down ) {
                    Vector2 toPosition = {
                        npc->actor.fromPosition.x,
                        floor(npc->actor.fromPosition.y / 32) * 32 + 32
                    };
                    if (!will_collide(toPosition)) {
                        npc->actor.toPosition.x = toPosition.x;
                        npc->actor.toPosition.y = toPosition.y;
                        npc->actor.moving = true;
                        npc->actor.movementDelay++;
                    } else {
                        npc->actor.moving = false;
                    }
                } else if ( npc->actor.direction == Up ) {
                    Vector2 toPosition = {
                        npc->actor.fromPosition.x,
                        floor(npc->actor.fromPosition.y / 32) * 32 - 32
                    };
                    if (!will_collide(toPosition)) {
                        npc->actor.toPosition.x = toPosition.x;
                        npc->actor.toPosition.y = toPosition.y;
                        npc->actor.moving = true;
                        npc->actor.movementDelay++;
                    } else {
                        npc->actor.moving = false;
                    }
                } else if ( npc->actor.direction == Left ) {
                    Vector2 toPosition = {
                        floor(npc->actor.fromPosition.x / 32) * 32 - 32,
                        npc->actor.fromPosition.y
                    };
                    if (!will_collide(toPosition)) {
                        npc->actor.toPosition.x = toPosition.x;
                        npc->actor.toPosition.y = toPosition.y;
                        npc->actor.moving = true;
                        npc->actor.movementDelay++;
                    } else {
                        npc->actor.moving = false;
                    }
                } else if ( npc->actor.direction == Right ) {
                    Vector2 toPosition = {
                        floor(npc->actor.fromPosition.x / 32) * 32 + 32,
                        npc->actor.fromPosition.y
                    };
                    if (!will_collide(toPosition)) {
                        npc->actor.toPosition.x = toPosition.x;
                        npc->actor.toPosition.y = toPosition.y;
                        npc->actor.moving = true;
                        npc->actor.movementDelay++;
                    } else {
                        npc->actor.moving = false;
                    }
                }
            }
            break;
        case Path:
            break;
    }

    if (npc->actor.moving && npc->actor.movementCounter < 8) {
        npc->actor.movementCounter++;
        // npc->actor.movementDelay = 0;
        npc->actor.position = lerp2( npc->actor.fromPosition, npc->actor.toPosition, npc->actor.movementCounter / 8.0f);
    }

    // Set the FROM position to the current position when we align with the grid
    if (npc->actor.moving && npc->actor.position.x == npc->actor.toPosition.x && npc->actor.position.y == npc->actor.toPosition.y) {
        npc->actor.fromPosition.x = npc->actor.toPosition.x;
        npc->actor.fromPosition.y = npc->actor.toPosition.y;
        npc->actor.moving = false;
        npc->actor.movementCounter = 0;
        npc->steps++;
    }
}
