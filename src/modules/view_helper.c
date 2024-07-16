#include <conio.h>

#include "view_helper.h"
#include "system_helper.h"

extern size_t xCellCoordinate;
extern size_t yCellCoordinate;

void showCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth )
{
    printCursorPosition();
    gotoxy( xCursorPosition, yCursorPosition );
    inverseAttributes();
    printf("%*s", fieldWidth, "" );
    restoreAttributes();
}

void hideCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth )
{
    gotoxy( xCursorPosition, yCursorPosition );
    printf("%*s", fieldWidth, "" );
}

void showColumnsHeaders( size_t fieldWidth, size_t rowHeadersWidth )
{
    char column = 'A';
    inverseAttributes();
    gotoxy( 0, 3 );
    printf( "%*c", rowHeadersWidth, ' ' );
    gotoxy( rowHeadersWidth, 3 );
    for ( size_t counter = 1; counter * fieldWidth < SCREEN_WIDTH - rowHeadersWidth; counter++ ) 
    {
        printf( "%-*c", fieldWidth, column + counter - 1 );
    }
    restoreAttributes();
}

void showRowsHeaders( size_t fieldWidth, size_t start ) 
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
    showColumnsHeaders( fieldWidth, rowHeadersWidth );
    showRowsHeaders( rowHeadersWidth, 1 );
    showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );

    while ( ( key = cgetc() ) != 'q' ) 
    {   
        hideCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );

        switch ( key ) 
        {
            case 0x0a:
            case 's':
                if ( yCursorPosition < SCREEN_HEIGHT  ) 
                {
                    yCursorPosition++;
                    yCellCoordinate++;
                }
                else
                {
                    yCursorPosition = SCREEN_HEIGHT;
                    
                    if ( yCellCoordinate < NUM_OF_ROWS - 1 )
                    {
                        yCellCoordinate++;
                        showRowsHeaders( rowHeadersWidth, yCellCoordinate - 18 );
                    }
                }
                break;
            case 0x0b:
            case 'w':
                if ( yCursorPosition > 4 ) 
                {
                    yCursorPosition--;
                    yCellCoordinate--;
                }
                else
                {
                    yCursorPosition = 4;
                    
                    if ( yCellCoordinate >= 1 )
                    {
                        yCellCoordinate--;
                        showRowsHeaders( rowHeadersWidth, yCellCoordinate + 1 );
                    }
                }
                break;
            case 0x09:
            case 'd':
                if ( xCursorPosition < SCREEN_WIDTH - fieldWidth - rowHeadersWidth )  
                {
                    xCursorPosition += fieldWidth;
                    xCellCoordinate++;
                }
                break;
            case 0x08:
            case 'a':
                if ( xCursorPosition > rowHeadersWidth ) 
                {
                    xCursorPosition -= fieldWidth;
                    xCellCoordinate--;
                }
                break;
        }

        showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );
    }
}

void showStatusBar( void )
{
    inverseAttributes();
    printf( "%*s", SCREEN_WIDTH, " " );
    gotoxy( 0, 1 );
    printf( "%*s", SCREEN_WIDTH, " " );
    restoreAttributes();
}

void printCursorPosition( void )
{
    inverseAttributes();
    gotoxy( 0, 0 );
    printf( "%c%d  ", 'A' + xCellCoordinate, yCellCoordinate + 1 );
    restoreAttributes();
}