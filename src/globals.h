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
#include "Maps/map.h"

extern display_context_t disp;
extern sprite_t *player_sprite;
extern sprite_t *npc_ghost;
extern sprite_t *aang_sprite;
extern sprite_t *peach_sprite;
extern sprite_t *yugi_sprite;
extern sprite_t *rick_sprite;
extern sprite_t *map_tile_texture_0;
extern sprite_t *map_tile_texture_1;
extern sprite_t *map_tile_texture_2;
extern sprite_t *map_tile_texture_3;
extern sprite_t *map_tile_texture_4;
extern sprite_t *map_tile_texture_5;
extern sprite_t *map_tile_texture_6;
extern sprite_t *map_tile_texture_7;
extern sprite_t *map_tile_texture_8;
extern sprite_t *map_tile_texture_9;
extern sprite_t *map_tile_texture_10;
extern sprite_t *map_tile_texture_11;
extern sprite_t *map_tile_texture_12;
extern sprite_t *map_tile_texture_13;
extern sprite_t *map_tile_texture_14;
extern sprite_t *map_tile_texture_15;
extern sprite_t *map_tile_texture_16;
extern sprite_t **map_tile_texture[17];
extern Vector2 screen_size;
extern Vector2 screen_relative_position;
extern Vector2 screen_relative_position_prior;
extern npc_t *npcs[32];
extern size_t npcs_count;
extern player_t player;
extern bool menu_open;
extern map_t *map;

#endif /* __BREADCODES_GLOBALS_H */