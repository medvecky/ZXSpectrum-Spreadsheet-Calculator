#include "command_helper.h"
#include "system_helper.h"
#include "input_helper.h"
#include "view_helper.h"

extern size_t xCellCoordinate;
extern size_t yCellCoordinate;

void handleKeyPress( char key,  size_t * xCursorPosition, size_t * yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
{
    switch ( key ) 
    {
        case 0x0a:
        case 'j':
        case 'J':
            handleDownKey( yCursorPosition, *xCursorPosition, rowHeadersWidth, fieldWidth );
            break;
        case 0x0b:
        case 'k':
        case 'K':
            handleUpKey( yCursorPosition, *xCursorPosition, rowHeadersWidth, fieldWidth );
            break;
        case 0x09:
        case 'l':
        case 'L':
            handleRightKey( xCursorPosition, *yCursorPosition, fieldWidth, rowHeadersWidth );
            break;
        case 0x08:
        case 'h':
        case 'H':
            handleLeftKey( xCursorPosition, *yCursorPosition, fieldWidth, rowHeadersWidth );
            break;
        case 'i':
        case 'I':
            handleInput();
            break;
        case 'd':
        case 'D':
            handleDeleteCell();
            break;
        
    }
}

void handleDownKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth )
{
    if ( *yCursorPosition < SCREEN_HEIGHT  ) 
    {
        ( *yCursorPosition )++;
        yCellCoordinate++;
    }
    else
    {
        *yCursorPosition = SCREEN_HEIGHT;
        
        if ( yCellCoordinate < NUMBER_OF_ROWS - 1 )
        {
            printLoadingOnStatusBar();
            yCellCoordinate++;
            showRowsHeaders( rowHeadersWidth, yCellCoordinate - 18 );
            size_t xShift = ( ( xCursorPosition - rowHeadersWidth ) / fieldWidth );
            displaySheetDataToGrid( fieldWidth, rowHeadersWidth, yCellCoordinate - 19, xCellCoordinate - xShift, downScroolCheck);
        }
    }
}

void handleUpKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth )
{
    if ( *yCursorPosition > 4 ) 
    {
        ( *yCursorPosition )--;
        yCellCoordinate--;
    }
    else
    {
        *yCursorPosition = 4;
        
        if ( yCellCoordinate >= 1 )
        {
            printLoadingOnStatusBar();
            yCellCoordinate--;
            showRowsHeaders( rowHeadersWidth, yCellCoordinate + 1 );
            size_t xShift = ( ( xCursorPosition - rowHeadersWidth ) / fieldWidth );
            displaySheetDataToGrid( fieldWidth, rowHeadersWidth, yCellCoordinate, xCellCoordinate - xShift, upScroolCheck );
        }
    }
}

void handleRightKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
{
    if ( *xCursorPosition < SCREEN_WIDTH - fieldWidth - rowHeadersWidth )  
    {
        ( *xCursorPosition ) += fieldWidth;
        xCellCoordinate++;
    }
    else
    {
        *xCursorPosition = SCREEN_WIDTH - fieldWidth - rowHeadersWidth;
        
        if ( xCellCoordinate < NUMBER_OF_COLUMNS - 1 )
        {
            printLoadingOnStatusBar();
            xCellCoordinate++;
            showColumnsHeaders( fieldWidth, rowHeadersWidth, xCellCoordinate - 4 );
            displaySheetDataToGrid( fieldWidth, rowHeadersWidth, yCellCoordinate - yCursorPosition + 4, xCellCoordinate - 4, rightScroolCheck );
        }
    }
}

void handleLeftKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
{
    if ( *xCursorPosition > rowHeadersWidth ) 
    {
        ( *xCursorPosition ) -= fieldWidth;
        xCellCoordinate--;
    }
    else
    {
        *xCursorPosition = rowHeadersWidth;
        
        if ( xCellCoordinate > 0 )
        {
            printLoadingOnStatusBar();
            xCellCoordinate--;
            showColumnsHeaders( fieldWidth, rowHeadersWidth, xCellCoordinate );
            displaySheetDataToGrid( fieldWidth, rowHeadersWidth, yCellCoordinate - yCursorPosition + 4, xCellCoordinate, leftScroolCheck);
        }
    }
}

void handleDeleteCell( void )
{
    Sheet_clearCell( sheet, yCellCoordinate, xCellCoordinate );
}

bool rightScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y, x - 1 );
}

bool leftScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y, x + 1 );
}

bool upScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y + 1, x );
}

bool downScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y - 1, x );
}