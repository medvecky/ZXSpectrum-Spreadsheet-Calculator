#ifndef ADT_BLANK_CELL_H
#define ADT_BLANK_CELL_H

#include "adt_cell.h"

typedef struct 
{
    Cell base;
} BlankCell;

void BlankCell_print( Cell * cell );
BlankCell * BlankCell_create(); 

#endif // ADT_BLANK_CELL_H