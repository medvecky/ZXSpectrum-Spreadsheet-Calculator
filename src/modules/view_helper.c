#include <conio.h>

#include "view_helper.h"
#include "system_helper.h"
#include "adt_sheet.h"

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
    displaySheetDataToGrid( fieldWidth, rowHeadersWidth, 0, 0 );
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

static void printValueToStatusBar()
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
        case 's':
            handleDownKey( yCursorPosition, rowHeadersWidth );
            break;
        case 0x0b:
        case 'w':
            handleUpKey( yCursorPosition, rowHeadersWidth );
            break;
        case 0x09:
        case 'd':
            handleRightKey( xCursorPosition, fieldWidth, rowHeadersWidth );
            break;
        case 0x08:
        case 'a':
            handleLeftKey( xCursorPosition, fieldWidth, rowHeadersWidth );
            break;
    }
}

static void handleDownKey( size_t * yCursorPosition, size_t rowHeadersWidth )
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
            yCellCoordinate++;
            showRowsHeaders( rowHeadersWidth, yCellCoordinate - 18 );
        }
    }
}

static void handleUpKey( size_t * yCursorPosition, size_t rowHeadersWidth )
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
            yCellCoordinate--;
            showRowsHeaders( rowHeadersWidth, yCellCoordinate + 1 );
        }
    }
}

static void handleRightKey( size_t * xCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
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
            xCellCoordinate++;
            showColumnsHeaders( fieldWidth, rowHeadersWidth, xCellCoordinate - 4 );
        }
    }
}

static void handleLeftKey( size_t * xCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
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
            xCellCoordinate--;
            showColumnsHeaders( fieldWidth, rowHeadersWidth, xCellCoordinate );
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

static void  displaySheetDataToGrid( size_t fieldWidth, size_t rowHeadersWidth, size_t startRow, size_t startColumn )
{
    for ( size_t rowCounter = 1; rowCounter < SCREEN_HEIGHT - 2; rowCounter++ )
    {
        for ( size_t colCounter = 1; colCounter * fieldWidth < SCREEN_WIDTH - rowHeadersWidth; colCounter++ )
        {
            gotoxy( rowHeadersWidth + ( colCounter - 1 ) * fieldWidth, rowCounter + 3 );
            printCellAtXYValue( colCounter - 1 + startColumn, rowCounter - 1 + startRow, fieldWidth );
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