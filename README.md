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
  - [ ] Map Builder (external tool)
  - [ ] Tilemap Renderer from Map Builder's Binaries

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
