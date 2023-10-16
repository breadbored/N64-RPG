all: breadcodes.z64
.PHONY: all

BUILD_DIR = build
include $(N64_INST)/include/n64.mk

SRC = src/main.c src/globals.c src/utils.c src/Actor/actor.c src/Actor/player.c src/Actor/npc.c src/Maps/map.c
OBJS = $(SRC:%.c=$(BUILD_DIR)/%.o)
DEPS = $(SRC:%.c=$(BUILD_DIR)/%.d)

SPRITE_DIR=filesystem
PNG_DIR=assets
SPRITE_MANIFEST_TXT := $(PNG_DIR)/manifest.txt
MKSPRITE := mksprite
REDIRECT_STDOUT := >/dev/null

breadcodes.z64: N64_ROM_TITLE = "breadcodes"
breadcodes.z64: $(BUILD_DIR)/breadcodes.dfs

$(BUILD_DIR)/breadcodes.dfs: $(wildcard filesystem/*)
$(BUILD_DIR)/breadcodes.elf: $(OBJS)

clean:
	rm -rf $(BUILD_DIR) *.z64
.PHONY: clean

assets:
	mksprite 16 2 2 assets/venusaur.png filesystem/venusaur.sprite
	mksprite 16 9 2 assets/aang.png filesystem/aang.sprite
	mksprite 16 3 4 assets/player.png filesystem/player.sprite
	mksprite 16 3 4 assets/npc_ghost.png filesystem/npc_ghost.sprite
	mksprite 16 9 2 assets/peach.png filesystem/peach.sprite
	mksprite 16 9 2 assets/yugi.png filesystem/yugi.sprite
	mksprite 16 9 1 assets/rick.png filesystem/rick.sprite
	mksprite 16 1 1 assets/cursor.png filesystem/cursor.sprite
	mksprite 16 8 133 assets/tileset.png filesystem/tileset.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_0.png filesystem/tileset_0.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_1.png filesystem/tileset_1.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_2.png filesystem/tileset_2.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_3.png filesystem/tileset_3.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_4.png filesystem/tileset_4.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_5.png filesystem/tileset_5.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_6.png filesystem/tileset_6.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_7.png filesystem/tileset_7.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_8.png filesystem/tileset_8.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_9.png filesystem/tileset_9.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_10.png filesystem/tileset_10.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_11.png filesystem/tileset_11.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_12.png filesystem/tileset_12.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_13.png filesystem/tileset_13.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_14.png filesystem/tileset_14.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_15.png filesystem/tileset_15.sprite
	mksprite 16 8 8 tileset_generated_parts/tileset_16.png filesystem/tileset_16.sprite
.PHONY: assets

libdragon-tools:
	cd libdragon/ && make tools install
.PHONY: tools

-include $(DEPS)
