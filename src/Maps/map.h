/**
 * @file map.h
 */
#ifndef __MAP_H
#define __MAP_H

#include <libdragon.h>
#include <math.h>
#include "../utils.h"

typedef enum map_items_t {
    NONE = -1,
    GRASS = 0,
    GRASS_DARK = 1,
    GRASS_LIGHT = 2,
    GRASS_DRY = 3,
    GRASS_WHEAT = 4,
    STONE = 5,
    SAND = 6,
    GRAVEL = 7,

    TREE_LIGHT_TL = 8,
    TREE_LIGHT_TR = 9,
    TREE_LIGHT_BL = 16,
    TREE_LIGHT_BR = 17,

    TREE_DARK_TL = 10,
    TREE_DARK_TR = 11,
    TREE_DARK_BL = 18,
    TREE_DARK_BR = 19,

    TREE_3_TL = 12,
    TREE_3_TR = 13,
    TREE_3_BL = 20,
    TREE_3_BR = 21,
} map_items_t;

typedef struct map_t {
    int width;
    int height;
    const int *bg_map;
    const int *fg0_map;
    const int *fg1_map;
    const int *fg2_map;
    const int *collision_map;
    npc_t **npcs;
    uint8_t npcs_count;
} map_t;

typedef struct map_tile_t {
    int tile;
    Vector2 position;
} map_tile_t;

Vector2 get_screen_position(Vector2 position);

void map_draw(map_t *map, sprite_t ***sprite_arr, uint8_t layer);

#endif /* __MAP_H */
