#ifndef VIEW_HELPER_H
#define VIEW_HELPER_H

#include <stdio.h>

#include "adt_sheet.h"

typedef bool ( * DirectionCheck )( size_t, size_t );

static void showCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth );
static void hideCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth );
static void showColumnsHeaders( size_t fieldWidth, size_t rowHeadersWidth, size_t start );
static void showRowsHeaders( size_t fieldWidth, size_t start);
void showGrid( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );
static void showStatusBar( void );
static void printCursorPosition( void );
static void handleKeyPress( char key,  size_t * xCursorPosition, size_t * yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );
static void handleDownKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth );
static void handleUpKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth );
static void handleRightKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );
static void handleLeftKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );
static void numberToTwoLetterCode( int number, char * symbol1, char * symbol2 );
static void printValueToStatusBar( void );
static void displaySheetDataToGrid( size_t fieldWidth, size_t rowHeadersWidth, size_t startRow, size_t startColumn, DirectionCheck directionCheck );
static void displayInitialSheetDataToGrid( size_t fieldWidth, size_t rowHeadersWidth );
static void printCellAtXYValue( size_t x, size_t y, size_t fieldWidth );
static void printLoadingOnStatusBar( void );
static bool rightScroolCheck( size_t x, size_t y );
static bool leftScroolCheck( size_t x, size_t y );
static bool upScroolCheck( size_t x, size_t y );
static bool downScroolCheck( size_t x, size_t y );
static void handleDeleteCell( void );

#endif