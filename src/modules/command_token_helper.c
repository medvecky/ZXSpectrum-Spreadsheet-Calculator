#include <stdbool.h>
#include <stdio.h>
#include <conio.h>

#include "command_token_helper.h"
#include "system_helper.h"

extern bool isRunning;

void handleCommandToken( void )
{
    showCommandHintInStatusBar( "Command", "S" );
    getAndHandleCommand();
    clearStatusBarCommandHint();
}

void showCommandHintInStatusBar( char * categoryHint, char * commandHint )
{
    inverseAttributes();
    
    gotoxy( 0, 1 );
    printf( "%s: %s                   ", categoryHint, commandHint );

    restoreAttributes();
}

void getAndHandleCommand( void )
{
    char command = cgetc();

    switch ( command )
    {
        case 's':
        case 'S':
            handleStorageCommand();
            break;
    }
}

void handleStorageCommand( void )
{
    showCommandHintInStatusBar( "Storage", "Q" );

    char command = cgetc();

    switch ( command )
    {
        case 'q':
        case 'Q':
            isRunning = false;
            break;
    }
}

void clearStatusBarCommandHint( void )
{
    inverseAttributes();
    gotoxy( 0, 1 );
    printf( "%*s", SCREEN_WIDTH, " " );
    restoreAttributes();
}
