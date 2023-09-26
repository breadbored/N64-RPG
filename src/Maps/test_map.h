/**
 * @file test_map.h
 */
#ifndef __TEST_MAP_H
#define __TEST_MAP_H

#include <libdragon.h>
#include <math.h>
#include "../utils.h"
#include "../Actor/npc.h"
#include "map.h"

npc_t testNpc1;
npc_t testNpc2;
npc_t testNpc3;
npc_t testNpc4;
npc_t testNpc5;
npc_t testNpc6;
npc_t testNpc7;

const int test_map_width = 15;
const int test_map_height = 10;
map_items_t test_bg_map[150]; // All default to 0 / GRASS
map_items_t test_fg_map[150] = {
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TREE_DARK_TL,  TREE_DARK_TR,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, TREE_DARK_BL,  TREE_DARK_BR,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
    NONE, NONE, NONE, TREE_LIGHT_TL,    TREE_LIGHT_TR,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
    NONE, NONE, NONE, TREE_LIGHT_BL,    TREE_LIGHT_BR,  NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
    NONE, NONE, NONE, NONE,             NONE,           NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,          NONE,
}; // All default to 0
npc_t *test_npcs[32] = {
    &testNpc1,
    &testNpc2,
    &testNpc3,
    &testNpc4,
    &testNpc5,
    &testNpc6,
    &testNpc7,
};
const uint8_t test_npcs_length = 7;

map_t test_map = {
    test_map_width,
    test_map_height,
    test_bg_map,
    test_fg_map,
    test_npcs,
    test_npcs_length,
};

#endif /* __TEST_MAP_H */
