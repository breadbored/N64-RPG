# RPG Engine for the Nintendo 64

## About

This unnamed project is an attempt to write all the parts of an RPG from scratch. Below is the list of features currently being written:

- [x] Actors
- [x] Player
- [x] Camera
- [x] NPCs
- [x] Collision
- [ ] Map Rendering
  - [x] Background (Landscape) Tilemap
  - [x] Foreground (Structure / Building) Tilemap
  - [ ] NPC Map Layer
  - [ ] Entrance/Exit Layer
    - [ ] Entrance/Exit Triggers
    - [ ] Map Switching
  - [x] Map Builder (external tool; Tiled)
  - [x] Tilemap Renderer from Map Builder's Binaries

## Setup

If you are on Windows, you will need to first set up WSL to get a linux environment in Windows

You will need to install the following (if you are using WSL, you will need to install inside that environment):

- Docker
- NodeJS >v18
- NPM

To get libdragon setup, you will need to run the following:

- Make sure the Docker daemon is running
- `npm i libdragon -g`
- `cd /path/to/this/project`
- `libdragon init`

To build the project:

- `libdragon make assets`
- `libdragon make`

This will produce an N64 ROM  called `breacodes.z64`

## Playing

### The best way to play is on a real Nintendo 64 via a flashcart

However if you must use an emulator, you must use an accurate emulator such as Ares. Common emulators are ***not*** accurate. They are typically optimized to run official games at a good speed, but are not hardware accurate. `libdragon` is a different from the official SDK, and most emulators cover emulation for the official SDK only, meaning it requires hardware accuracy or specially built support.


## Editing the map

To make the map, I used software called [Tiled](https://thorbjorn.itch.io/tiled?download). You can find the project file at `map/n64-rpg.tiled-project`. I export as a CSV called `overworld.csv` and it will generate a CSV for each layer. 

To build the mpa, run the included tool with `python3 tools/makemap.py` to generate the map file.

Important notes:

I work only in the positive area (0,0) and higher. Do not add any tiles in the negative coordinates or it will shift the entire map.

Tiled does not export with perfect coordinates in CSV format, so every layer must have a tile in the (0,0) coordinate. This is to prevent offset problems. For example, the background layer has a grass tile at (0,0), and the foreground layer has a tree.