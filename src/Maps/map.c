#include <libdragon.h>
#include <math.h>
#include "../globals.h"
#include "../utils.h"
#include "map.h"

Vector2 get_screen_position(Vector2 position) {
    return (Vector2) {
        position.x - screen_relative_position.x,
        position.y - screen_relative_position.y
    };
}

void draw_section(map_t *map, sprite_t *sprite, map_items_t *tilemap) {
    map_items_t last_tile_texture = NONE;
    for (size_t x = 0; x < map->width; x++) {
        for (size_t y = 0; y < map->height; y++) {
            map_items_t tile = tilemap[x + y * map->width];
            if (tile == NONE) continue;
            Vector2 screen_position = get_screen_position((Vector2) { x * 32, y * 32 });
            if (screen_position.x < -32 || screen_position.x > screen_size.x + 32 || screen_position.y < -32 || screen_position.y > screen_size.y + 32) {
                continue;
            }
            rdp_sync( SYNC_PIPE );
            if (last_tile_texture != tile) {
                rdp_load_texture_stride( 0, 0, MIRROR_DISABLED, sprite, tile );
                last_tile_texture = tile;
            }
            rdp_draw_sprite( 0, screen_position.x, screen_position.y, MIRROR_DISABLED );
        }
    }
}

void map_draw(map_t *map, sprite_t *sprite)
{
    draw_section(map, sprite, map->bg_map);
    draw_section(map, sprite, map->fg_map);
}
