/**
 * @file globals.h
 * @brief Globals
 */
#ifndef __BREADCODES_GLOBALS_H
#define __BREADCODES_GLOBALS_H

#include <libdragon.h>
#include "utils.h"
#include "Actor/npc.h"
#include "Actor/player.h"

extern Vector2 screen_size;
extern Vector2 screen_relative_position;
extern npc_t *npcs[32];
extern size_t npcs_count;
extern player_t player;

#endif /* __BREADCODES_GLOBALS_H */