#ifndef ADT_SHEET_H
#define ADT_SHEET_H

#include <stdbool.h>

#include "adt_cell.h"
#include "system_helper.h"

typedef struct 
{
    Cell * cells[ NUMBER_OF_ROWS ][ NUMBER_OF_COLUMNS ];
} Sheet;

Sheet * Sheet_create();
void Sheet_setCell( Sheet * sheet, int row, int col, Cell * cell );
Cell * Sheet_getCell( Sheet * sheet, int row, int col );
bool Sheet_isEmpty( Sheet * sheet, int row, int col );

#endif // ADT_SHEET_H