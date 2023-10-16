#include <libdragon.h>
#include <math.h>
#include "../globals.h"
#include "../utils.h"
#include "actor.h"

void actor_init(actor_t *actor, sprite_t *sprite, Vector2 position)
{
    actor->position = position;
    actor->moving = false;
    actor->movementCounter = 0;
    actor->movementDelay = 0;
    actor->direction = Down;
    actor->fromPosition = position;
    actor->toPosition = position;
    actor->sprite = sprite;
}

int actor_frame(actor_t *actor, uint32_t *animcounter) {
    int playerFrame = 0;
    if (!actor->moving) {
        if (actor->direction == Down) {
            playerFrame = 0;
        } else if (actor->direction == Up) {
            playerFrame = 1;
        } else if (actor->direction == Left) {
            playerFrame = 2;
        } else if (actor->direction == Right) {
            playerFrame = 2;
        }
    } else {
        int frameCount = ((*animcounter) / 2) % 4;
        if (actor->direction == Down) {
            if (frameCount == 1 || frameCount == 3) playerFrame = 0;
            else playerFrame = 3 + (frameCount / 2);
        } else if (actor->direction == Up) {
            if (frameCount == 1 || frameCount == 3) playerFrame = 1;
            else playerFrame = 5 + (frameCount / 2);
        } else if (actor->direction == Left) {
            if (frameCount == 1 || frameCount == 3) playerFrame = 2;
            else playerFrame = 7 + (frameCount / 2);
        } else if (actor->direction == Right) {
            if (frameCount == 1 || frameCount == 3) playerFrame = 2;
            else playerFrame = 7 + (frameCount / 2);
        }
    }
    return playerFrame;
}

void actor_draw(actor_t *actor, uint32_t *animcounter) {
    Vector2 screen_coordinates = get_screen_coordinates(actor->position);

    // Do not render if the actor is outside the screen
    if (screen_coordinates.x < -64 || screen_coordinates.x > screen_size.x + 64 || screen_coordinates.y < -64 || screen_coordinates.y > screen_size.y + 64) {
        return;
    }

    int actorFrame = actor_frame(actor, animcounter);
    rdp_sync( SYNC_PIPE );
    rdp_load_texture_stride( 0, 0, actor->direction == Right ? MIRROR_X : MIRROR_DISABLED, actor->sprite, actorFrame );
    rdp_draw_sprite( 0, screen_coordinates.x, screen_coordinates.y, actor->direction == Right ? MIRROR_X : MIRROR_DISABLED );
}

bool will_collide(actor_t *actor, Vector2 toPosition) {
    if (&((&player)->actor) != actor) {
        // If NPC is moving, check if it will collide with the player
        if ((player.actor.position.x == toPosition.x && player.actor.position.y == toPosition.y) || (player.actor.toPosition.x == toPosition.x && player.actor.toPosition.y == toPosition.y)) {
            return true;
        }
    }
    // NPCs and Player need to check collisions with each other
    for (size_t i = 0; i < npcs_count; i++) {
        npc_t *npc = npcs[i];
        if ((npc->actor.position.x == toPosition.x && npc->actor.position.y == toPosition.y) || (npc->actor.toPosition.x == toPosition.x && npc->actor.toPosition.y == toPosition.y)) {
            return true;
        }
    }
    // Check collisions with walls
    Vector2 toTile = (Vector2) { toPosition.x / 32, toPosition.y / 32 };
    Vector2 fromTile = (Vector2) { actor->fromPosition.x / 32, actor->fromPosition.y / 32 };
    if (toTile.x < 0 || toTile.y < 0 || toTile.x >= map->width || toTile.y >= map->height) {
        return true;
    }
    // Non-conditional collisions have an id of 0, interactive collisions have an id of 1
    if (map->collision_map[toTile.x + toTile.y * map->width] == 0 || map->collision_map[toTile.x + toTile.y * map->width] == 1) {
        return true;
    }

    // Check collision with foreground objects (implying standing on a raised surface) and green collisions
    // Used to keep the player from walking off a ledge
    if (map->fg0_map[fromTile.x + fromTile.y * map->width] != NONE && map->collision_map[toTile.x + toTile.y * map->width] == 3) {
        return true;
    }

    // Check collision with green collisions (implying standing on a lower surface) and foreground objects (a raised surface)
    // Used to keep the player from walking up a ledge
    if (map->fg0_map[toTile.x + toTile.y * map->width] != NONE && map->collision_map[fromTile.x + fromTile.y * map->width] == 3) {
        return true;
    }
    
    return false;
}
