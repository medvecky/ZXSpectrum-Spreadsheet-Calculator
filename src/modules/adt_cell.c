#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void Cell_printBlank( Cell * cell, size_t fieldWidth ) 
{
    
}

void Cell_printNumber( Cell * cell, size_t fieldWidth ) 
{
    
    if ( fieldWidth > 0 ) 
    {
        int precision = fieldWidth - ( int )log10( cell->data.number ) - 1;
        if ( precision < 0 ) precision = 0;
        if ( precision > 2 ) precision -= 2;
        printf( "%.*f", precision , cell->data.number );
    } 
    else 
    {
        printf( "%-*f", fieldWidth, cell->data.number );
    }
}

void Cell_printText( Cell * cell, size_t fieldWidth ) 
{
    if ( fieldWidth > 0 ) 
    {
        size_t textLength = strlen( cell->data.text );
        if ( textLength > fieldWidth ) 
        {
            char * cutText = ( char * )malloc( ( fieldWidth + 1 ) * sizeof( char ) );
            strncpy( cutText, cell->data.text, fieldWidth );
            cutText[ fieldWidth - 1 ] = '\0';
            printf( "%-*s", fieldWidth, cutText );
            free( cutText ) ;
        } 
        else 
        {
            printf( "%-*s", fieldWidth, cell->data.text );
        }
    } 
    else 
    {
        printf( "%s", cell->data.text );
    }
}   