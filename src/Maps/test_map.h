/**
 * @file test_map.h
 */
#ifndef __TEST_MAP_H
#define __TEST_MAP_H

#include <libdragon.h>
#include <math.h>
#include "../utils.h"
#include "map.h"

const int test_map_width = 15;
const int test_map_height = 10;
map_items_t test_bg_map[150]; // All default to 0 / GRASS
map_items_t test_fg_map[150] = {
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, TREE_LIGHT_TL,    TREE_LIGHT_TR,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, TREE_LIGHT_BL,    TREE_LIGHT_BR,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
}; // All default to 0 / NONE

map_t test_map = {
    test_map_width,
    test_map_height,
    test_bg_map,
    test_fg_map
};

#endif /* __TEST_MAP_H */
