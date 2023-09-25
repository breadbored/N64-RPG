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
    map_items_t *bg_map;
    map_items_t *fg_map;
} map_t;

Vector2 get_screen_position(Vector2 position);

void map_draw(map_t *map, sprite_t *sprite);

#endif /* __MAP_H */