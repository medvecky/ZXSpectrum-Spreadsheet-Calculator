#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "modules/system_helper.h"
#include "modules/view_helper.h"
#include "modules/adt_sheet.h"

size_t xCellCoordinate = 0;
size_t yCellCoordinate = 0;

int main( void )
{
    size_t fieldWidth = 7;
    size_t rowHeadersWidth = 3;
    size_t xCursorPosition = rowHeadersWidth;
    size_t yCursorPosition = 4;

    setUpScreen();
    
    // showGrid( xCursorPosition, yCursorPosition, fieldWidth, rowHeadersWidth );
    Sheet * sheet = Sheet_create();
    Cell * cell = Cell_createNumber( 3.14 );
    Sheet_setCell( sheet, 0, 0, cell );
    cell = Cell_createText( "Hello, world" );
    Sheet_setCell( sheet, 0, 1, cell );
    Cell * cellOut = Sheet_getCell( sheet, 0, 0 );
    cellOut->print( cellOut );
    puts( "" );
    cellOut = Sheet_getCell( sheet, 0, 1 );
    cellOut->print( cellOut );
    puts( "" );
    printf( "Size of Cell %d\n", sizeof( Cell ) );
    printf( "Size of Sheet %d\n", sizeof( Sheet ) );
    puts( "Press any key to exit..." );

    cgetc();

    restoreScreen();
    
    return EXIT_SUCCESS;
}
