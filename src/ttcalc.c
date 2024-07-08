#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "modules/system_helper.h"
#include "modules/view_helper.h"

int main( void )
{
    size_t fieldWidth = 7;
    size_t xCursorPosition = fieldWidth;
    size_t yCursorPosition = 1;
    char key = 0;


    setUpScreen();
    
    showColumnsHeaders( fieldWidth );
    showRowsHeaders( fieldWidth );
    showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );

    while ( ( key = cgetc() ) != 'q' ) 
    {   
        hideCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );

        switch ( key ) 
        {
            // case 0x0a:
            case 's':
                if ( yCursorPosition < SCREEN_HEIGHT  ) 
                {
                    yCursorPosition++;
                }
                break;
            // case 0x0b:
            case 'w':
                if ( yCursorPosition > 1 ) 
                {
                    yCursorPosition--;
                }
                break;
            // case 0x09:
            case 'd':
                if ( xCursorPosition < SCREEN_WIDTH - fieldWidth - 1) 
                {
                    xCursorPosition += fieldWidth;
                }
                break;
            // case 0x08:
            case 'a':
                if ( xCursorPosition > fieldWidth ) 
                {
                    xCursorPosition -= fieldWidth;
                }
                break;
        }

        showCursorAtXY( xCursorPosition, yCursorPosition, fieldWidth );
    }

    restoreScreen();
    
    return EXIT_SUCCESS;
}
