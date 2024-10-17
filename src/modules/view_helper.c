#include <conio.h>
#include <ctype.h>

#include "view_helper.h"
#include "system_helper.h"
#include "adt_sheet.h"
#include "input_helper.h"

extern size_t xCellCoordinate;
extern size_t yCellCoordinate;

static void showCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth )
{
    printCursorPosition();
    printValueToStatusBar();
    
    gotoxy( xCursorPosition, yCursorPosition );
    inverseAttributes();

    if ( Sheet_isEmpty( sheet, yCellCoordinate, xCellCoordinate ) ) 
    {
        printf( "%*s", fieldWidth, "" );
    } 
    else 
    {
        printCellAtXYValue( xCellCoordinate, yCellCoordinate, fieldWidth );
    }
    
    restoreAttributes();
}

static void hideCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth )
{
    gotoxy( xCursorPosition, yCursorPosition );
    
    if ( Sheet_isEmpty( sheet, yCellCoordinate, xCellCoordinate ) ) 
    {
        printf( "%*s", fieldWidth, "" );
    } 
    else 
    {
        printCellAtXYValue( xCellCoordinate, yCellCoordinate, fieldWidth );
    }
}

static void showColumnsHeaders( size_t fieldWidth, size_t rowHeadersWidth, size_t start )
{
    char column = 'A';
    inverseAttributes();
    gotoxy( 0, 3 );
    printf( "%*c", rowHeadersWidth, ' ' );
    gotoxy( rowHeadersWidth, 3 );
    for ( size_t counter = 1; counter * fieldWidth < SCREEN_WIDTH - rowHeadersWidth; counter++ ) 
    {
        char columnSymbol =  ' ';
        char secondColumnSymbol = ' ';
        numberToTwoLetterCode( counter + start, &columnSymbol, &secondColumnSymbol );
        if ( columnSymbol != ' ' ) 
        {
            printf( "%c%c%*s", columnSymbol, secondColumnSymbol, fieldWidth - 2, "" );
        } 
        else 
        {
            printf( "%c%*s", secondColumnSymbol, fieldWidth - 1, "" );
        }
    }
    restoreAttributes();
}

static void showRowsHeaders( size_t fieldWidth, size_t start ) 
{
    inverseAttributes();
    for ( size_t counter = 1; counter <= SCREEN_HEIGHT - 3; counter++ ) 
    {
        gotoxy( 0, counter + 3 );
        printf( "%-*d", fieldWidth, counter + start - 1 );
    }
    restoreAttributes();
}

void showGrid( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
{
    char key = 0;
    showStatusBar();
    showColumnsHeaders( fieldWidth, rowHeadersWidth, 0 );
    showRowsHeaders( rowHeadersWidth, 1 );
    printLoadingOnStatusBar();
    displayInitialSheetDataToGrid( fieldWidth, rowHeadersWidth );
    showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );

    while ( ( key = cgetc() ) != 'q' ) 
    {   
        hideCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );
        handleKeyPress( key, &xCursorPosition, &yCursorPosition, fieldWidth, rowHeadersWidth );
        showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );
    }
}

static void showStatusBar( void )
{
    inverseAttributes();
    printf( "%*s", SCREEN_WIDTH, " " );
    gotoxy( 0, 1 );
    printf( "%*s", SCREEN_WIDTH, " " );
    restoreAttributes();
}

static void printCursorPosition( void )
{
    char columnSymbol = ' ';
    char secondColumnSymbol = ' ';
    inverseAttributes();
    gotoxy( 0, 0 );
    numberToTwoLetterCode( xCellCoordinate + 1, &columnSymbol, &secondColumnSymbol );

    if ( xCellCoordinate + 1 <= 26 ) 
    {
        printf( "%c%d    ", secondColumnSymbol, yCellCoordinate + 1 );
    } 
    else 
    {
        printf( "%c%c%d   ", columnSymbol, secondColumnSymbol, yCellCoordinate + 1 );
    }
    
    restoreAttributes();
}

static void printValueToStatusBar( void )
{
    inverseAttributes();

    if ( Sheet_isEmpty( sheet, yCellCoordinate, xCellCoordinate ) ) 
    {
        printf( "                    " );
    } 
    else 
    {
        Cell * cell = Sheet_getCell( sheet, yCellCoordinate, xCellCoordinate );
        if ( cell->type == NUMBER_CELL ) 
        {
            printf( "%s", "(V)" );
        } 
        else if ( cell->type == TEXT_CELL )   
        {
            printf( "%s", "(L)" );
        }

        printf( "%s", " " );
        cell->print( cell, 0 );
        printf( "%s", "                  " );
    }

    restoreAttributes();
}   

static void handleKeyPress( char key,  size_t * xCursorPosition, size_t * yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
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

static void handleDownKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth )
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

static void handleUpKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth )
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

static void handleRightKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
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

static void handleLeftKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
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

static void numberToTwoLetterCode( int number, char * symbol1, char * symbol2 ) 
{
    if ( number <= 26 ) 
    {
        // If the number is 26 or less, only one symbol is needed.
        *symbol1 = ' '; // No first symbol needed, so it's set to null character.
        *symbol2 = ( char )( ( number - 1 ) % 26 + 'A' );
    } 
    else 
    {
        *symbol1 = ( char )( ( number / 26 ) + 'A' - 1 ); // Calculate the first symbol.
        *symbol2 = ( char )( ( number % 26 ) + 'A' - 1 ); // Calculate the second symbol.

        if ( *symbol2 == '@' ) 
        {
            *symbol2 = 'Z';
            ( *symbol1 )--;
        }
    }
}

static bool rightScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y, x - 1 );
}

static bool leftScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y, x + 1 );
}

static bool upScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y + 1, x );
}

static bool downScroolCheck( size_t x, size_t y )
{
    return !Sheet_isEmpty( sheet, y, x ) ||  !Sheet_isEmpty( sheet, y - 1, x );
}

static void  displaySheetDataToGrid( size_t fieldWidth, size_t rowHeadersWidth, size_t startRow, size_t startColumn, DirectionCheck directionCheck )
{
    for ( size_t rowCounter = 1; rowCounter < SCREEN_HEIGHT - 2; rowCounter++ )
    {
        for ( size_t colCounter = 1; colCounter * fieldWidth < SCREEN_WIDTH - rowHeadersWidth; colCounter++ )
        {
            gotoxy( rowHeadersWidth + ( colCounter - 1 ) * fieldWidth, rowCounter + 3 );
            // printCellAtXYValue( colCounter - 1 + startColumn, rowCounter - 1 + startRow, fieldWidth );
            size_t x = colCounter - 1 + startColumn;
            size_t y = rowCounter - 1 + startRow;
            
            if ( directionCheck( x, y ) )
            {
                if ( !Sheet_isEmpty( sheet, y, x ) )    
                {
                    Cell * cell = Sheet_getCell( sheet, y, x );
                    cell->print( cell , fieldWidth );
                }
                else 
                {
                    printf( "%*s", fieldWidth, "" );
                }
            }
        }
    }
}

static void  displayInitialSheetDataToGrid( size_t fieldWidth, size_t rowHeadersWidth )
{
    for ( size_t rowCounter = 1; rowCounter < SCREEN_HEIGHT - 2; rowCounter++ )
    {
        for ( size_t colCounter = 1; colCounter * fieldWidth < SCREEN_WIDTH - rowHeadersWidth; colCounter++ )
        {
            gotoxy( rowHeadersWidth + ( colCounter - 1 ) * fieldWidth, rowCounter + 3 );
            // printCellAtXYValue( colCounter - 1 + startColumn, rowCounter - 1 + startRow, fieldWidth );
            size_t x = colCounter - 1;
            size_t y = rowCounter - 1;            
            if ( !Sheet_isEmpty( sheet, y, x ) ) 
            {
                Cell * cell = Sheet_getCell( sheet, y, x );
                cell->print( cell , fieldWidth );
            }
        }
    }
} 

static void printCellAtXYValue( size_t x, size_t y, size_t fieldWidth )
{
    if ( !Sheet_isEmpty( sheet, y, x ) ) 
    {
        Cell * cell = Sheet_getCell( sheet, y, x );
        cell->print( cell , fieldWidth );
    }
    else 
    {
        printf( "%*s", fieldWidth, "" );
    }
}

static void printLoadingOnStatusBar( void )
{
    inverseAttributes();
    gotoxy( 0, 0 );
    printf( "%s", "Loading...                         " );
    restoreAttributes();
}

void handleDeleteCell( void )
{
    Sheet_clearCell( sheet, yCellCoordinate, xCellCoordinate );
}