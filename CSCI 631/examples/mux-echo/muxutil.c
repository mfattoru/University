#include "muxecho.h"

void init_flags ( )
{
    int i;

    for ( i = 0; i < NFLAGS; i++ )
        exit_flags [ i ] = true;
}
