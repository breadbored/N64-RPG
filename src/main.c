#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>
#include <math.h>
#include "globals.h"
#include "utils.h"
#include "Actor/actor.h"
#include "Actor/player.h"
#include "Actor/npc.h"

static uint32_t animcounter = 0;
const bool DEBUG = false;

void controller_handle(void);

void update( int ovfl )
{
    animcounter++;
    for (size_t i = 0; i < npcs_count; i++) {
        npc_update(npcs[i], animcounter);
    }
    controller_handle();
}

/**
 * Mouse State
 */
Vector2 cursorPosition = { 0, 0 };
uint32_t controllerData1 = 0x00000000;
uint32_t controllerData2 = 0x00000000;

npc_t testNpc1;
npc_t testNpc2;
npc_t testNpc3;
npc_t testNpc4;
npc_t testNpc5;
npc_t testNpc6;
npc_t testNpc7;

void controller_handle(void) {
    /* Do we need to switch video displays? */
    controller_scan();
    struct controller_data keys = get_keys_pressed();

    controllerData1 = keys.c[0].data;
    controllerData2 = keys.c[1].data;

    // Copying to another struct because I can't find the type
    // TODO: Don't fucking do that
    controller_state_t controller_1_state;
    controller_1_state.A = keys.c[0].A;
    controller_1_state.B = keys.c[0].B;
    controller_1_state.Z = keys.c[0].Z;
    controller_1_state.L = keys.c[0].L;
    controller_1_state.R = keys.c[0].R;
    controller_1_state.up = keys.c[0].up;
    controller_1_state.down = keys.c[0].down;
    controller_1_state.left = keys.c[0].left;
    controller_1_state.right = keys.c[0].right;
    controller_1_state.C_up = keys.c[0].C_up;
    controller_1_state.C_down = keys.c[0].C_down;
    controller_1_state.C_left = keys.c[0].C_left;
    controller_1_state.C_right = keys.c[0].C_right;
    controller_1_state.start = keys.c[0].start;
    controller_1_state.x = keys.c[0].x;
    controller_1_state.y = keys.c[0].y;
    controller_1_state.data = keys.c[0].data;

    player_handle_controller(&player, &controller_1_state);

    // Cursor Movement
    MouseData mouseData = get_mouse_value(controllerData2);
    cursorPosition.x += mouseData.deltaX;
    cursorPosition.y += mouseData.deltaY;
}

int main( void )
{
    /* Initialize peripherals */
    display_init( RESOLUTION_320x240, DEPTH_16_BPP, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE );
    dfs_init( DFS_DEFAULT_LOCATION );
    rdp_init();
    controller_init();
    timer_init();

    npcs[0] = &testNpc1;
    npcs[1] = &testNpc2;
    npcs[2] = &testNpc3;
    npcs[3] = &testNpc4;
    npcs[4] = &testNpc5;
    npcs[5] = &testNpc6;
    npcs[6] = &testNpc7;
    npcs_count = 7;

    /* Read in single sprite */
    int fp = dfs_open("/mudkip.sprite");
    sprite_t *mudkip = malloc( dfs_size( fp ) );
    dfs_read( mudkip, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    fp = dfs_open("/venusaur.sprite");
    sprite_t *venusaur = malloc( dfs_size( fp ) );
    dfs_read( venusaur, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    fp = dfs_open("/aang.sprite");
    sprite_t *aang = malloc( dfs_size( fp ) );
    dfs_read( aang, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    fp = dfs_open("/peach.sprite");
    sprite_t *peach = malloc( dfs_size( fp ) );
    dfs_read( peach, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    fp = dfs_open("/yugi.sprite");
    sprite_t *yugi = malloc( dfs_size( fp ) );
    dfs_read( yugi, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    fp = dfs_open("/rick.sprite");
    sprite_t *rick = malloc( dfs_size( fp ) );
    dfs_read( rick, 1, dfs_size( fp ), fp );
    dfs_close( fp );
    
    fp = dfs_open("/cursor.sprite");
    sprite_t *cursor = malloc( dfs_size( fp ) );
    dfs_read( cursor, 1, dfs_size( fp ), fp );
    dfs_close( fp );

    player_init(&player, aang, (Vector2){ -32, 0 });

    for (int i = 0; i < npcs_count; i++) {
        sprite_t* sprite = i % 3 == 0 ? rick : i % 3 == 1 ? peach : i % 3 == 2 ? yugi : aang;
        int ranAction = random_int(0, 8);
        npc_action_t action = ranAction % 4 == 0 ? Spin : ranAction % 4 == 1 ? Idle : ranAction % 4 == 2 ? Pace : Path;
        int ranDir = random_int(0, 8);
        direction_t direction = ranDir % 4 == 0 ? Up : ranDir % 4 == 1 ? Down : ranDir % 4 == 2 ? Left : Right;
        npc_init(npcs[i], sprite, (Vector2){ 32 * i + 32, 32 * (i % 2) + 32 }, direction, action, 10, 3);
    }

    /* Kick off animation update timer to fire thirty times a second */
    new_timer(TIMER_TICKS(1000000 / 30), TF_CONTINUOUS, update);

    /* Main loop test */
    while(1) 
    {
        static display_context_t disp = 0;

        /* Grab a render buffer */
        while( !(disp = display_lock()) );
       
        /*Fill the screen */
        graphics_fill_screen( disp, 0xFFFFFFFF );

        /* Set the text output color */
        graphics_set_color( 0x0, 0xFFFFFFFF );

        if (screen_size.x == 0 || screen_size.y == 0) {
            screen_size.x = disp->width;
            screen_size.y = disp->height;
        }
    
        /* 
            Hardware Rendering 
        */
        // graphics_draw_text( disp, ((disp->width * 7.0f) / 20.0f), 20, "@BreadCodes" );
        
        if (DEBUG) {
            int lenX = snprintf(NULL, 0, "%d", player.actor.toPosition.x);
            char *resultX = malloc(lenX + 1);
            snprintf(resultX, lenX + 1, "%d", player.actor.toPosition.x);
            graphics_draw_text( disp, ((disp->width * 7.0f) / 20.0f), 10, resultX );
            free(resultX);

            int lenY = snprintf(NULL, 0, "%d", player.actor.toPosition.y);
            char *resultY = malloc(lenY + 1);
            snprintf(resultY, lenY + 1, "%d", player.actor.toPosition.y);
            graphics_draw_text( disp, ((disp->width * 7.0f) / 20.0f), 30, resultY );
            free(resultY);

            int lenMC = snprintf(NULL, 0, "%u", player.actor.movementCounter);
            char *resultMC = malloc(lenMC + 1);
            snprintf(resultMC, lenMC + 1, "%u", player.actor.movementCounter);
            graphics_draw_text( disp, ((disp->width * 7.0f) / 20.0f), 50, resultMC );
            free(resultMC);

            int lenController1 = snprintf(NULL, 0, BIT32_TO_BINARY_PATTERN, U32_TO_BINARY(controllerData1));
            char *resultController1 = malloc(lenController1 + 1);
            snprintf(resultController1, lenController1 + 1, BIT32_TO_BINARY_PATTERN, U32_TO_BINARY(controllerData1));
            graphics_draw_text( disp, 10, 70, resultController1 );
            free(resultController1);

            int lenController2 = snprintf(NULL, 0, BIT32_TO_BINARY_PATTERN, U32_TO_BINARY(controllerData2));
            char *resultController2 = malloc(lenController2 + 1);
            snprintf(resultController2, lenController2 + 1, BIT32_TO_BINARY_PATTERN, U32_TO_BINARY(controllerData2));
            graphics_draw_text( disp, 10, 90, resultController2 );
            free(resultController2);

            MouseData mouseData = get_mouse_value(controllerData2);
            int lenMouseXY = snprintf(NULL, 0, "%d, %d", mouseData.deltaX, mouseData.deltaY);
            char *resultMouseXY = malloc(lenMouseXY + 1);
            snprintf(resultMouseXY, lenMouseXY + 1, "%d, %d", mouseData.deltaX, mouseData.deltaY);
            graphics_draw_text( disp, ((disp->width * 7.0f) / 20.0f), 110, resultMouseXY );
            free(resultMouseXY);
        }

#pragma region RDP Commands
        /* Assure RDP is ready for new commands */
        rdp_sync( SYNC_PIPE );

        /* Remove any clipping windows */
        rdp_set_default_clipping();

        /* Enable sprite display instead of solid color fill */
        rdp_enable_texture_copy();

        /* Attach RDP to display */
        rdp_attach_display( disp );
#pragma endregion Commands

        for (size_t i = 0; i < npcs_count; i++) {
            npc_draw(npcs[i], animcounter);
        }

        player_update(&player, animcounter);

        /* Inform the RDP we are finished drawing and that any pending operations should be flushed */
        rdp_detach_display();

        /* 
            End Hardware Rendering 
        */

        /* Force backbuffer flip */
        display_show(disp);
    }
}
