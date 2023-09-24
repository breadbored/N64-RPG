#include <libdragon.h>
#include "globals.h"
#include "utils.h"
#include "Actor/npc.h"

Vector2 screen_size = { 0, 0 };
Vector2 screen_relative_position = { 0, 0 };
npc_t *npcs[32];
size_t npcs_count = 0;
player_t player;