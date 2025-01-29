#include <conio.h>

#include "sheet_ops_helper.h"

void clearAllCellsInSheet( size_t fieldWidth, size_t rowHeadersWidth )
{
    for ( size_t rowCounter = 1; rowCounter < SCREEN_HEIGHT - 2; rowCounter++ )
    {
        for ( size_t colCounter = 1; colCounter * fieldWidth < SCREEN_WIDTH - rowHeadersWidth; colCounter++ )
        {
            gotoxy( rowHeadersWidth + ( colCounter - 1 ) * fieldWidth, rowCounter + 3 );
            size_t x = colCounter - 1;
            size_t y = rowCounter - 1;            
            if ( !Sheet_isEmpty( sheet, y, x ) ) 
            {
                Sheet_clearCell( sheet, y, x );
                printf( "%*s", fieldWidth, "" );
            } // end if cell is not empty
        } // end for loop for columns
    } // end for loop for rows
} // end function clearAllCellsInSheet

bool isCellEmpty( Sheet * sheet, size_t y, size_t x )
{
    return Sheet_isEmpty( sheet, y, x );
} // end function isCellEmpty

Sheet * createSheet( void )
{
    return Sheet_create();
} // end function createSheet

Cell * getCell( Sheet * sheet, size_t y, size_t x )
{
    return Sheet_getCell( sheet, y, x );
} // end function getCell