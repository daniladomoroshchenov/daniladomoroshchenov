#ifndef CS
#define CS
#include "GPSEphem.h"

typedef unsigned char u1;
enum
{
    bits = 8,
    lShift = 2,
    rShift = bits - lShift
};

#define ROT_LEFT(val) ((val << lShift) | (val >> rShift))

u1 cs(u1 const* src, int count)
{
    u1 res = 0;
    while (count--)
        res = ROT_LEFT(res) ^ *src++;
    return ROT_LEFT(res);
}

#endif
