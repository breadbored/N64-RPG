#include <libdragon.h>
#include "globals.h"
#include "utils.h"
#include "Actor/npc.h"

display_context_t disp;
sprite_t *aang_sprite;
sprite_t *peach_sprite;
sprite_t *yugi_sprite;
sprite_t *rick_sprite;
sprite_t *map_tile_texture_0;
sprite_t *map_tile_texture_1;
sprite_t *map_tile_texture_2;
sprite_t *map_tile_texture_3;
sprite_t *map_tile_texture_4;
sprite_t *map_tile_texture_5;
sprite_t *map_tile_texture_6;
sprite_t *map_tile_texture_7;
sprite_t *map_tile_texture_8;
sprite_t *map_tile_texture_9;
sprite_t *map_tile_texture_10;
sprite_t *map_tile_texture_11;
sprite_t *map_tile_texture_12;
sprite_t *map_tile_texture_13;
sprite_t *map_tile_texture_14;
sprite_t *map_tile_texture_15;
sprite_t *map_tile_texture_16;
sprite_t **map_tile_texture[17] = {
    &map_tile_texture_0,
    &map_tile_texture_1,
    &map_tile_texture_2,
    &map_tile_texture_3,
    &map_tile_texture_4,
    &map_tile_texture_5,
    &map_tile_texture_6,
    &map_tile_texture_7,
    &map_tile_texture_8,
    &map_tile_texture_9,
    &map_tile_texture_10,
    &map_tile_texture_11,
    &map_tile_texture_12,
    &map_tile_texture_13,
    &map_tile_texture_14,
    &map_tile_texture_15,
    &map_tile_texture_16,
};
Vector2 screen_size = { 0, 0 };
Vector2 screen_relative_position = { 0, 0 };
npc_t *npcs[32];
size_t npcs_count = 0;
player_t player;
bool menu_open = false;