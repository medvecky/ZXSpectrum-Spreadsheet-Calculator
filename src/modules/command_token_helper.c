#include <stdbool.h>
#include <stdio.h>
#include <conio.h>

#include "command_token_helper.h"
#include "system_helper.h"
#include "file_io_helper.h"
#include "input_helper.h"

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
    showCommandHintInStatusBar( "Storage", "S Q" );

    char command = cgetc();

    switch ( command )
    {
        case 'q':
        case 'Q':
            isRunning = false;
            break;
        case 's':
        case 'S':
            saveDataToDiskHandler();
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

void saveDataToDiskHandler( void )
{
    showCommandHintInStatusBar( "Storage", "File for Saving" );
    gotoxy( 0, 2 );
    char * fileName = getInputString();
    
    if ( saveDataToDisk( fileName ) == EXIT_FAILURE )
    {
        cgetc();    
    }

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
    free( fileName );
}