#ifndef SHEET_OPS_HELPER_H
#define SHEET_OPS_HELPER_H

#include <stdio.h>

#include "../view/system_helper.h"
#include "../model/adt_sheet.h"

void clearAllCellsInSheet( size_t fieldWidth, size_t rowHeadersWidth );
bool isCellEmpty( Sheet * sheet, size_t y, size_t x );
Sheet * createSheet( void );
Cell * getCell( Sheet * sheet, size_t y, size_t x );

#endif // SHEET_OPS_HELPER_H