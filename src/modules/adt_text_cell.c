#include <stdio.h>
#include <string.h>

#include "adt_text_cell.h"

void TextCell_print( Cell * cell ) 
{
    TextCell * txtCell = ( TextCell * )cell;
    printf( "%s", txtCell->text );
}

TextCell * TextCell_create( char * text ) 
{
    TextCell *cell = ( TextCell * )malloc( sizeof( TextCell ) );
    cell->base.type = "TextCell";
    cell->base.print = TextCell_print;
    cell->text = strdup( text );
    
    return cell;
}
