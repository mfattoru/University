#include "/home/cs631/common/631.h"
#include "/home/cs631/common/wrapper.h"

#ifndef H_MUX_ECHO
#define H_MUX_ECHO

extern bool exit_flags [ ];

void init_flags ( );
void str_cli ( FILE*, int );
void str_echo ( int );
#endif
