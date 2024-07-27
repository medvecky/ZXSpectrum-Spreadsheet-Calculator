#ifndef ADT_NUMBER_CELL_H
#define ADT_NUMBER_CELL_H

#include "adt_cell.h"

typedef struct 
{
    Cell base;
    double value;
} NumberCell;

void NumberCell_print( Cell * cell );
NumberCell * NumberCell_create( double value );

#endif // ADT_NUMBER_CELL_H