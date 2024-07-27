#include <stdlib.h>

#include "adt_sheet.h"
#include "adt_blank_cell.h"

Sheet * Sheet_create() 
{
    Sheet *sheet = ( Sheet * )malloc( sizeof( Sheet ) );
    
    for ( size_t r = 0; r < NUMBER_OF_ROWS; r++ ) 
    {
        for ( size_t c = 0; c < NUMBER_OF_COLUMNS; c++ ) 
        {
            sheet->cells[ r ][ c ] = ( Cell * )BlankCell_create();
        }
    }
    
    return sheet;
}

void Sheet_setCell( Sheet * sheet, int row, int col, Cell * cell ) 
{
    if ( row >= 0 && row < NUMBER_OF_ROWS && col >= 0 && col < NUMBER_OF_COLUMNS ) 
    {
        if ( sheet->cells[ row ][ col ] != NULL ) 
        {
            free( sheet->cells[ row ][ col ] );
        }
        
        sheet->cells[ row ][ col ] = cell;
    }
}