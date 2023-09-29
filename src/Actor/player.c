#include <libdragon.h>
#include <math.h>
#include "../globals.h"
#include "../utils.h"
#include "actor.h"
#include "player.h"

static const uint8_t movementDelayThreshold = 2;

void player_init(player_t *player, sprite_t *sprite, Vector2 position)
{
    actor_init(&(player->actor), sprite, position);
}

void player_draw(player_t *player, uint32_t animcounter)
{
    // This is only used to fix values for layers rendered after the player
    screen_relative_position_prior.x = screen_relative_position.x;
    screen_relative_position_prior.y = screen_relative_position.y;

    // This is used to calculate the screen position of the camera
    screen_relative_position.x = player->actor.position.x;
    screen_relative_position.y = player->actor.position.y;
    
    actor_draw(&(player->actor), &animcounter);
}

void player_handle_controller(player_t *player, controller_state_t *controller_state) {
    // Player Movement
    if (!(controller_state->up || controller_state->down || controller_state->left || controller_state->right)) {
        player->actor.movementDelay = 0;
    }

    if (!player->actor.moving) {
        if( controller_state->down && controller_state->down >= controller_state->up && controller_state->down >= controller_state->left && controller_state->down >= controller_state->right ) {
            player->actor.direction = Down;
            Vector2 toPosition = {
                player->actor.fromPosition.x,
                floor(player->actor.fromPosition.y / 32) * 32 + 32
            };
            if (player->actor.movementDelay > movementDelayThreshold && !will_collide(toPosition)) {
                player->actor.toPosition.x = toPosition.x;
                player->actor.toPosition.y = toPosition.y;
                player->actor.moving = true;
            }
            player->actor.movementDelay++;
        } else if ( controller_state->up && controller_state->up >= controller_state->down && controller_state->up >= controller_state->left && controller_state->up >= controller_state->right ) {
            player->actor.direction = Up;
            Vector2 toPosition = {
                player->actor.fromPosition.x,
                floor(player->actor.fromPosition.y / 32) * 32 - 32
            };
            if (player->actor.movementDelay > movementDelayThreshold && !will_collide(toPosition)) {
                player->actor.toPosition.x = toPosition.x;
                player->actor.toPosition.y = toPosition.y;
                player->actor.moving = true;
            }
            player->actor.movementDelay++;
        } else if ( controller_state->left && controller_state->left >= controller_state->down && controller_state->left >= controller_state->up && controller_state->left >= controller_state->right ) {
            player->actor.direction = Left;
            Vector2 toPosition = {
                floor(player->actor.fromPosition.x / 32) * 32 - 32,
                player->actor.fromPosition.y
            };
            if (player->actor.movementDelay > movementDelayThreshold && !will_collide(toPosition)) {
                player->actor.toPosition.x = toPosition.x;
                player->actor.toPosition.y = toPosition.y;
                player->actor.moving = true;
            }
            player->actor.movementDelay++;
        } else if ( controller_state->right && controller_state->right >= controller_state->down && controller_state->right >= controller_state->up && controller_state->right >= controller_state->left ) {
            player->actor.direction = Right;
            Vector2 toPosition = {
                floor(player->actor.fromPosition.x / 32) * 32 + 32,
                player->actor.fromPosition.y
            };
            if (player->actor.movementDelay > movementDelayThreshold && !will_collide(toPosition)) {
                player->actor.toPosition.x = toPosition.x;
                player->actor.toPosition.y = toPosition.y;
                player->actor.moving = true;
            }
            player->actor.movementDelay++;
        }
    }
    if (player->actor.moving && player->actor.movementCounter < 8) {
        player->actor.movementCounter++;
        // player->actor.movementDelay = 0;
        player->actor.position = lerp2( player->actor.fromPosition, player->actor.toPosition, player->actor.movementCounter / 8.0f);
    }

    // Set the FROM position to the current position when we align with the grid
    if (player->actor.moving && player->actor.position.x == player->actor.toPosition.x && player->actor.position.y == player->actor.toPosition.y) {
        player->actor.fromPosition.x = player->actor.toPosition.x;
        player->actor.fromPosition.y = player->actor.toPosition.y;
        player->actor.moving = false;
        player->actor.movementCounter = 0;
    }
}

