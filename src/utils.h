/**
 * @file utils.h
 * @brief Utility functions for the project
 * @ingroup utils
 */
#ifndef __BREADCODES_UTILS_H
#define __BREADCODES_UTILS_H

#include <libdragon.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BIT32_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c'%c%c%c%c%c%c%c%c'%c%c%c%c%c%c%c%c'%c%c%c%c%c%c%c%c"
#define BIT_REP(bit)           (bit ? '1' : '0')
#define BYTE_TO_BINARY(byte)   BIT_REP(byte & 0x80), BIT_REP(byte & 0x40), BIT_REP(byte & 0x20), BIT_REP(byte & 0x10), BIT_REP(byte & 0x08), BIT_REP(byte & 0x04), BIT_REP(byte & 0x02), BIT_REP(byte & 0x01) 
#define U32_TO_BINARY(final)   BYTE_TO_BINARY((final >> 24)), BYTE_TO_BINARY((final >> 16)), BYTE_TO_BINARY((final >> 8)), BYTE_TO_BINARY((final & 0xFF))

int random_int(int lower, int upper);
uint32_t rand(void);

typedef struct Vector2f
{
    float x;
    float y;
} Vector2f;

typedef struct Vector2
{
    int x;
    int y;
} Vector2;

typedef struct MouseData
{
    bool A;
    bool B;
    signed char deltaX;
    signed char deltaY;
} MouseData;

float lerpf( float a, float b, float t );

int lerp( int a, int b, float t );

Vector2f lerp2f( Vector2f a, Vector2f b, float t );

Vector2 lerp2( Vector2 a, Vector2 b, float t );

bool are_same(float x, float y);

MouseData get_mouse_value( uint32_t controllerData );

Vector2 get_screen_coordinates(Vector2 position);

int clamp(int value, int min, int max);

#endif /* __BREADCODES_UTILS_H */