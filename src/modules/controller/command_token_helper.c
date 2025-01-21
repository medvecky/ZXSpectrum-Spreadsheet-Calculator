#include <stdbool.h>
#include <stdio.h>
#include <conio.h>

#include "command_token_helper.h"
#include "../view/system_helper.h"
#include "file_io_helper.h"
#include "input_helper.h"
#include "../view/view_helper.h"

extern bool isRunning;

void handleCommandToken( size_t fieldWidth, size_t rowHeadersWidth )
{
    showCommandHintInStatusBar( "Command", "S C" );
    getAndHandleCommand( fieldWidth, rowHeadersWidth );
    clearStatusBarCommandHint();
}

void showCommandHintInStatusBar( char * categoryHint, char * commandHint )
{
    inverseAttributes();
    
    gotoxy( 0, 1 );
    printf( "%s: %s", categoryHint, commandHint );

    restoreAttributes();
}

void getAndHandleCommand( size_t fieldWidth, size_t rowHeadersWidth )
{
    char command = cgetc();

    switch ( command )
    {
        case 's':
        case 'S':
            handleStorageCommand( fieldWidth, rowHeadersWidth );
            break;
        case 'c':
        case 'C':
            handleClearCommand( fieldWidth, rowHeadersWidth );
            break;
    }
}

void handleStorageCommand( size_t fieldWidth, size_t rowHeadersWidth )
{
    showCommandHintInStatusBar( "Storage", "S W L R Q" );

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
        case 'l':
        case 'L':
            loadDataFromDiskHandler();
            displayInitialSheetDataToGrid( fieldWidth, rowHeadersWidth );
            break;
        case 'w':
        case 'W':
            saveDataToTapeHandler();
            break;  
        case 'r':
        case 'R':
            loadDataFromTapeHandler();
            displayInitialSheetDataToGrid( fieldWidth, rowHeadersWidth );
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
    printLoadingOnStatusBar();

    if ( saveDataToDisk( fileName ) == EXIT_FAILURE )
    {
        showCommandHintInStatusBar( "Error", "Failed to write data to disk" );
        cgetc();    
    }

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
    free( fileName );
}

void loadDataFromDiskHandler( void )
{
    showCommandHintInStatusBar( "Storage", "File to Load" );
    gotoxy( 0, 2 );
    char * fileName = getInputString();
    printLoadingOnStatusBar();

    if ( loadDataFromDisk( fileName ) == EXIT_FAILURE )
    {
        showCommandHintInStatusBar( "Error", "Failed to load data from disk" );
        cgetc();    
    }

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
    free( fileName );
}

void saveDataToTapeHandler( void )
{
    showCommandHintInStatusBar( "Storage", "Start the tape and press any key" );
    cgetc();
    printLoadingOnStatusBar();

    if ( seriliazeTableDataToTape() == EXIT_FAILURE )
    {
        showCommandHintInStatusBar( "Error", "Failed to write to tape           " );
        cgetc();    
    }

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
}

void loadDataFromTapeHandler( void )
{
    showCommandHintInStatusBar( "Storage", "Load From Tape" );
    printLoadingOnStatusBar();

    if ( deSerializeTableDataFromTape() == EXIT_FAILURE )
    {
        showCommandHintInStatusBar( "Error", "Failed to load from tape          " );
        cgetc();    
    }

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " ); 
}

void handleClearCommand( size_t fieldWidth, size_t rowHeadersWidth )
{
    showCommandHintInStatusBar( "Clear", "Type Y to confirm" );
    char command = cgetc();
    if ( command == 'y' || command == 'Y' )
    {
        printLoadingOnStatusBar();
        clearAllCellsInSheet( fieldWidth, rowHeadersWidth );
    }
   
    clearStatusBarCommandHint();
}