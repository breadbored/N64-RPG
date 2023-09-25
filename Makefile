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
	mksprite 16 9 2 assets/peach.png filesystem/peach.sprite
	mksprite 16 9 2 assets/yugi.png filesystem/yugi.sprite
	mksprite 16 9 1 assets/rick.png filesystem/rick.sprite
	mksprite 16 1 1 assets/cursor.png filesystem/cursor.sprite
	mksprite 16 8 133 assets/tileset.png filesystem/tileset.sprite
.PHONY: assets

libdragon-tools:
	cd libdragon/ && make tools install
.PHONY: assets

-include $(DEPS)
