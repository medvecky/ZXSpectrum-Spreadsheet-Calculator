#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "modules/system_helper.h"
#include "modules/view_helper.h"

int main( void )
{
    size_t fieldWidth = 7;
    size_t rowHeadersWidth = 3;
    size_t xCursorPosition = rowHeadersWidth;
    size_t yCursorPosition = 1;

    setUpScreen();
    
    showGrid( xCursorPosition, yCursorPosition, fieldWidth, rowHeadersWidth );

    restoreScreen();
    
    return EXIT_SUCCESS;
}
