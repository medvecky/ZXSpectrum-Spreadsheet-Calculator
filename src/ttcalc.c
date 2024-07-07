#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "modules/system_helper.h"

int main( void )
{
    size_t xCursorPosition = 0;
    size_t yCursorPosition = 0;
    size_t fieldWidth = 7;
    char key = 0;

    setUpScreen();
    
    gotoxy( 0,0 );
    inverseAttributes();
    printf("%*s", fieldWidth, "" );
    restoreAttributes();

    while ( ( key = cgetc() ) != 'q' ) 
    {   
        gotoxy( xCursorPosition, yCursorPosition );
        printf("%*s", fieldWidth, "" );

        switch ( key ) 
        {
            case 0x0a:
                if ( yCursorPosition < SCREEN_HEIGHT ) 
                {
                    yCursorPosition++;
                }
                break;
            case 0x0b:
                if ( yCursorPosition > 0 ) 
                {
                    yCursorPosition--;
                }
                break;
            case 0x09:
                if ( xCursorPosition < SCREEN_WIDTH - fieldWidth - 1) 
                {
                    xCursorPosition += fieldWidth;
                }
                break;
            case 0x08:
                if ( xCursorPosition > 0 ) 
                {
                    xCursorPosition -= fieldWidth;
                }
                break;
        }

        gotoxy( xCursorPosition, yCursorPosition );
        inverseAttributes();
        printf("%*s", fieldWidth, "" );
        restoreAttributes();
    }

    restoreScreen();
    
    return EXIT_SUCCESS;
}
