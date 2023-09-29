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
Vector2 get_prior_screen_position(Vector2 position) {
    return (Vector2) {
        position.x - screen_relative_position_prior.x + ((screen_size.x / 2) - 16),
        position.y - screen_relative_position_prior.y + ((screen_size.y / 2) - 16)
    };
}

Vector2 get_map_position(Vector2 position) {
    return (Vector2) {
        position.x + screen_relative_position.x - ((screen_size.x / 2) - 16),
        position.y + screen_relative_position.y - ((screen_size.y / 2) - 16)
    };
}

int mmin(int a, int b) {
    return a < b ? a : b;
}

int mmax(int a, int b) {
    return a > b ? a : b;
}

void draw_section(map_t *map, sprite_t **sprite_arr, const int *tilemap, bool rendered_after_player) {
    Vector2 start_position = get_map_position((Vector2) { -32, -32 });
    Vector2 end_position = get_map_position((Vector2) { screen_size.x + 32, screen_size.y + 32 });
    Vector2 start_tile = (Vector2) { start_position.x / 32, start_position.y / 32 };
    Vector2 end_tile = (Vector2) { end_position.x / 32, end_position.y / 32 };

    // Because rdp_load_texture_stride is expensive and causes a frame drop when called many times, 
    // we only load the texture when it changes.
    // This can be heavily optimized further by presorting an array of the texture index and 
    // vector2 of the tile coordinates.
    // That could be used to only load a texture once for all tiles of that type.
    int last_tile_texture = NONE;
    for (size_t x = start_tile.x; x < end_tile.x; x++) {
        for (size_t y = start_tile.y; y < end_tile.y; y++) {
            Vector2 screen_position = rendered_after_player ? 
                get_prior_screen_position((Vector2) { x * 32, y * 32 }) :   // Only for layers rendered after the player
                get_screen_position((Vector2) { x * 32, y * 32 });          // Only for layers rendered before the player

            // If the coord is outside the map, render default grass
            if (x < 0 || y < 0 || x >= map->width || y >= map->height) {
                if (last_tile_texture != GRASS_DARK) {
                    sprite_t *sprite = *(map_tile_texture[GRASS_DARK / (8*8)]);
                    rdp_sync( SYNC_PIPE );
                    rdp_load_texture_stride( 0, 0, MIRROR_DISABLED, sprite, GRASS_DARK % (8*8) );
                    last_tile_texture = GRASS_DARK;
                }
                rdp_draw_sprite( 0, screen_position.x, screen_position.y, MIRROR_DISABLED );
                continue; // Skip everything else
            }

            // If the tile is empty, don't render
            int tile = tilemap[x + y * map->width];
            if (tile == NONE) continue;

            // If the tile is outside the screen, don't render
            if (screen_position.x < -32 || screen_position.x > screen_size.x + 32 || screen_position.y < -32 || screen_position.y > screen_size.y + 32) {
                continue;
            }

            // Only load textures as often as they change, and only load the texture if it's not already loaded
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

void map_draw(map_t *map, sprite_t ***sprite_arr, uint8_t layer)
{
    if (layer == 0) {
        draw_section(map, (*sprite_arr), map->bg_map, false);
        return;
    } else if (layer == 1) {
        draw_section(map, (*sprite_arr), map->fg0_map, false);
        return;
    } else if (layer == 2) {
        // Since this layer comes after the player (to layer over them), we need to adjust the offset
        draw_section(map, (*sprite_arr), map->fg1_map, true);
        return;
    }
}
