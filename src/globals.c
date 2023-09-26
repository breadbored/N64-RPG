#include <libdragon.h>
#include "globals.h"
#include "utils.h"
#include "Actor/npc.h"

sprite_t *aang_sprite;
sprite_t *peach_sprite;
sprite_t *yugi_sprite;
sprite_t *rick_sprite;
sprite_t *map_tile_texture;
Vector2 screen_size = { 0, 0 };
Vector2 screen_relative_position = { 0, 0 };
npc_t *npcs[32];
size_t npcs_count = 0;
player_t player;
bool menu_open = false;