#include <stdlib.h>
#include <stdio.h>

#include "adt_sheet.h"

Sheet * Sheet_create() 
{
    Sheet *sheet = ( Sheet * )malloc( sizeof( Sheet ) );
    
    for ( size_t r = 0; r < NUMBER_OF_ROWS; r++ ) 
    {
        for ( size_t c = 0; c < NUMBER_OF_COLUMNS; c++ ) 
        {
            sheet->cells[ r ][ c ] = NULL;
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
            if ( sheet->cells[ row ][ col ]->type == TEXT_CELL ) 
            {
                free( sheet->cells[ row ][ col ]->data.text );
            }
            
            free( sheet->cells[ row ][ col ] );
        }
        
        sheet->cells[ row ][ col ] = cell;
    }
}

Cell * Sheet_getCell( Sheet * sheet, int row, int col ) 
{
    Cell * cell = NULL;

    if ( row >= 0 && row < NUMBER_OF_ROWS && col >= 0 && col < NUMBER_OF_COLUMNS ) 
    {
        cell = sheet->cells[ row ][ col ];
    }

    return cell;
}

bool Sheet_isEmpty( Sheet * sheet, int row, int col ) 
{
    return ( row < 0 || row >= NUMBER_OF_ROWS || col < 0 || col >= NUMBER_OF_COLUMNS || sheet->cells[ row ][ col ] == NULL );
}