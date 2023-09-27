#include <libdragon.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../globals.h"
#include "../utils.h"
#include "map.h"

Vector2 get_screen_position(Vector2 position) {
    return (Vector2) {
        position.x - screen_relative_position.x + ((screen_size.x / 2) - 16),
        position.y - screen_relative_position.y + ((screen_size.y / 2) - 16)
    };
}

void draw_section(map_t *map, sprite_t **sprite_arr, const int *tilemap) {
    // Because rdp_load_texture_stride is expensive and causes a frame drop when called many times, 
    // we only load the texture when it changes.
    // This can be heavily optimized further by presorting an array of the texture index and 
    // vector2 of the tile coordinates.
    // That could be used to only load a texture once for all tiles of that type.
    int last_tile_texture = NONE;
    for (size_t x = 0; x < map->width; x++) {
        for (size_t y = 0; y < map->height; y++) {
            int tile = tilemap[x + y * map->width];
            if (tile == NONE) continue;
            Vector2 screen_position = get_screen_position((Vector2) { x * 32, y * 32 });
            if (screen_position.x < -32 || screen_position.x > screen_size.x + 32 || screen_position.y < -32 || screen_position.y > screen_size.y + 32) {
                continue;
            }
            if (last_tile_texture != tile) {
                sprite_t *sprite = *(map_tile_texture[tile / (8*8)]);
                rdp_sync( SYNC_PIPE );
                rdp_load_texture_stride( 0, 0, MIRROR_DISABLED, sprite, tile % (8*8) );
                last_tile_texture = tile;
            }
            rdp_draw_sprite( 0, screen_position.x, screen_position.y, MIRROR_DISABLED );
        }
    }
}

void map_draw(map_t *map, sprite_t ***sprite_arr)
{
    draw_section(map, (*sprite_arr), map->bg_map);
    draw_section(map, (*sprite_arr), map->fg_map);
}
