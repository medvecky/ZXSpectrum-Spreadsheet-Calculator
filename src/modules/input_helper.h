#ifndef INPUT_HELPER_H
#define INPUT_HELPER_H

#include <stdbool.h>

#include "adt_cell.h"

#define MAX_INPUT_LENGTH 80

int handleInput( void );
Cell * createCell( void );
char * getInputString( void );
bool isNumber( const char * str );

#endif // INPUT_HELPER_H