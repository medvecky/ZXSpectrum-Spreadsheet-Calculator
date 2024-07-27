#ifndef ADT_TEXT_CELL_H
#define ADT_TEXT_CELL_H

#include "adt_cell.h"

typedef struct 
{
    Cell base;
    char * text;
} TextCell;

void TextCell_print( Cell * cell );
TextCell * TextCell_create( char * text );

#endif // ADT_TEXT_CELL_H