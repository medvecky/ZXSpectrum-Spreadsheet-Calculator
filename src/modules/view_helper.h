#ifndef VIEW_HELPER_H
#define VIEW_HELPER_H

#include <stdio.h>

void showCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth );
void hideCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth );
void showColumnsHeaders( size_t fieldWidth, size_t rowHeadersWidth );
void showRowsHeaders( size_t fieldWidth );
void showGrid( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );

#endif