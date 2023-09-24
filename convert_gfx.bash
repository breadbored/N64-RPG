#!/usr/bin/env bash
#
# Convert pngs into 16-bit libdragon sprites
#

set -euo pipefail

# Provide sensible defaults, but these should be set by the Makefile
[ -z ${MKSPRITE+x} ] && MKSPRITE="libdragon/tools/mksprite/mksprite"
[ -z ${PNG_DIR+x} ] && PNG_DIR="resources/gfx"
[ -z ${SPRITE_DIR+x} ] && SPRITE_DIR="build/filesystem/gfx"

# Ensure the `mksprite` command exists
command -v ${MKSPRITE} >/dev/null 2>&1 || { \
  echo >&2 'This script requires the `mksprite` command.'; \
  echo >&2 'Run `make libdragon-tools` to resolve this issue.'; \
  exit 1; \
}

PNG_EXT=".png"
SPRITE_EXT=".sprite"
MANIFEST="${PNG_DIR}/manifest.txt"
BIT_DEPTH=16

convert_png_to_sprite() {
    local PNG_FILE=$1
    FILE_BASENAME=$(basename -s ${PNG_EXT} ${PNG_FILE})
    # Look up the file in the manifest
    LINE=$(egrep "^${FILE_BASENAME}\s+" ${MANIFEST})
    # Assume a 1x1 sprite if it's not in the manifest
    if [ -z "$LINE" ]; then
        echo >&2 "WARNING: PNG file '${PNG_FILE}' is not in the manifest!"
        LINE="${FILE_BASENAME} 1 1"
    fi
    convert_manifest_line_to_sprite "$LINE"
}

convert_manifest_line_to_sprite() {
    local META_LINE=$1
    # Convert META_LINE into an array
    read -a META <<<$META_LINE
    # Get metadata from META array
    FILE_BASENAME=${META[0]}
    H_SLICES=${META[1]}
    V_SLICES=${META[2]}
    # Build a sprite from the filenames and slicing metadata
    PNG_FILE="${PNG_DIR}/${FILE_BASENAME}${PNG_EXT}"
    SPRITE_FILE="${SPRITE_DIR}/${FILE_BASENAME}${SPRITE_EXT}"
    $MKSPRITE $BIT_DEPTH $H_SLICES $V_SLICES $PNG_FILE $SPRITE_FILE
}

mkdir -p ${SPRITE_DIR}

if [ $# -eq 0 ]; then
    # Loop through the manifest and convert everything
    while read LINE; do
      convert_manifest_line_to_sprite "${LINE}"
    done < ${MANIFEST}
else
    # Convert command-line arguments
    for FILE in "$@"; do
        if [ -z $FILE ]
        then
            echo "No arguments supplied"
        fi

        convert_png_to_sprite "${FILE}"
    done
fi
