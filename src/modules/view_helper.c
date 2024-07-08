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

void showColumnsHeaders( size_t fieldWidth )
{
    char column = 'A';
    inverseAttributes();
    gotoxy( fieldWidth, 0 );
    for ( size_t counter = 1; counter * fieldWidth < SCREEN_WIDTH; counter++ ) 
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