#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "modules/system_helper.h"
#include "modules/view_helper.h"

size_t xCellCoordinate = 0;
size_t yCellCoordinate = 0;

int main( void )
{
    size_t fieldWidth = 7;
    size_t rowHeadersWidth = 3;
    size_t xCursorPosition = rowHeadersWidth;
    size_t yCursorPosition = 4;

    setUpScreen();
    
    showGrid( xCursorPosition, yCursorPosition, fieldWidth, rowHeadersWidth );

    restoreScreen();
    
    return EXIT_SUCCESS;
}
