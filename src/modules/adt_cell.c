#include <stdio.h>
#include <stdlib.h>

#include "adt_cell.h"

Cell * Cell_createBlank() 
{
    Cell * cell = ( Cell * )malloc( sizeof( Cell ) );
    cell->type = BLANK_CELL;
    cell->print = Cell_printBlank;
    return cell;
}

Cell * Cell_createNumber( double number ) 
{
    Cell * cell = ( Cell * )malloc( sizeof( Cell ) );
    cell->type = NUMBER_CELL;
    cell->data.number = number;
    cell->print = Cell_printNumber;
    return cell;
}

Cell * Cell_createText( char * text ) 
{
    Cell * cell = ( Cell * )malloc( sizeof( Cell ) );
    cell->type = TEXT_CELL;
    cell->data.text = text;
    cell->print = Cell_printText;
    return cell;
}

void Cell_printBlank( Cell * cell ) 
{
    
}

void Cell_printNumber( Cell * cell ) 
{
    printf( "%f", cell->data.number );
}

void Cell_printText( Cell * cell ) 
{
    printf( "%s", cell->data.text );
}   