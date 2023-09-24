#include <libdragon.h>
#include <math.h>
#include "utils.h"

static uint32_t rand_state = 8888;
uint32_t rand(void) {
	uint32_t x = rand_state;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 5;
	return rand_state = x;
}
int random_int(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

float lerpf( float a, float b, float t )
{
    return (1.0f - t) * a + t * b;
}

int lerp( int a, int b, float t )
{
    return (int)lerpf( (float)a, (float)b, t );
}

Vector2f lerp2f( Vector2f a, Vector2f b, float t )
{
    Vector2f result;
    result.x = lerpf(a.x, b.x, t);
    result.y = lerpf(a.y, b.y, t);
    return result;
}

Vector2 lerp2( Vector2 a, Vector2 b, float t )
{
    Vector2 result;
    result.x = lerp(a.x, b.x, t);
    result.y = lerp(a.y, b.y, t);
    return result;
}

bool are_same(float x, float y)
{
    return fabs(x - y) < 0.000001f;
}

MouseData get_mouse_value( uint32_t controllerData )
{
    MouseData value;
    value.A = (controllerData & 0x80000000) != 0;
    value.B = (controllerData & 0x40000000) != 0;
    value.deltaX =      (signed char)(((controllerData & 0x0000FF00) >> 8) & 0xFF);
    value.deltaY = -1 * (signed char)( (controllerData & 0x000000FF)       & 0xFF);
    return value;
}
