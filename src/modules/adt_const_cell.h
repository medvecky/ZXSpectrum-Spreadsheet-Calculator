#ifndef ADT_CONST_CELL_H
#define ADT_CONST_CELL_H

#include "adt_cell.h"
#include "adt_blank_cell.h"
#include "adt_number_cell.h"
#include "adt_text_cell.h"

typedef struct 
{
    Cell base;
    union 
    {
        BlankCell blankCell;
        NumberCell numberCell;
        TextCell textCell;
    } data;
} ConstCell;

#endif // ADT_CONST_CELL_H