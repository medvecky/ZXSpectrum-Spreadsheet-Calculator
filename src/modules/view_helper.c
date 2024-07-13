#include <conio.h>

#include "view_helper.h"
#include "system_helper.h"

void showCursorAtXY( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth )
{
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
    printf( "%*c", rowHeadersWidth, ' ' );
    gotoxy( rowHeadersWidth, 0 );
    for ( size_t counter = 1; counter * fieldWidth < SCREEN_WIDTH - rowHeadersWidth; counter++ ) 
    {
        printf( "%-*c", fieldWidth, column + counter - 1 );
    }
    restoreAttributes();
}

void showRowsHeaders( size_t fieldWidth )
{
    inverseAttributes();
    for ( size_t counter = 1; counter <= SCREEN_HEIGHT; counter++ ) 
    {
        gotoxy( 0, counter );
        printf( "%-*d", fieldWidth, counter );
    }
    restoreAttributes();
}

void showGrid( size_t xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth )
{
    char key = 0;
    showColumnsHeaders( fieldWidth, rowHeadersWidth );
    showRowsHeaders( rowHeadersWidth );
    showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );

    while ( ( key = cgetc() ) != 'q' ) 
    {   
        hideCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );

        switch ( key ) 
        {
            case 0x0a:
            // case 's':
                if ( yCursorPosition < SCREEN_HEIGHT  ) 
                {
                    yCursorPosition++;
                }
                break;
            case 0x0b:
            // case 'w':
                if ( yCursorPosition > 1 ) 
                {
                    yCursorPosition--;
                }
                break;
            case 0x09:
            // case 'd':
                if ( xCursorPosition < SCREEN_WIDTH - fieldWidth - rowHeadersWidth )  
                {
                    xCursorPosition += fieldWidth;
                }
                break;
            case 0x08:
            // case 'a':
                if ( xCursorPosition > rowHeadersWidth ) 
                {
                    xCursorPosition -= fieldWidth;
                }
                break;
        }

        showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );
    }
}