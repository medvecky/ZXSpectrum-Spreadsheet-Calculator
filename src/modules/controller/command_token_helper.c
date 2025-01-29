#include <stdbool.h>
#include <stdio.h>
#include <conio.h>

#include "command_token_helper.h"
#include "file_io_helper.h"
#include "input_helper.h"
#include "sheet_ops_helper.h"

#include "../view/view_helper.h"
#include "../view/system_helper.h"

extern bool isRunning;

void handleCommandToken( size_t fieldWidth, size_t rowHeadersWidth )
{
    showCommandHintInStatusBar( "Command", "S C" );
    getAndHandleCommand( fieldWidth, rowHeadersWidth );
    clearStatusBarCommandHint();
} // end function handleCommandToken

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
    } // end switch command
} // end function getAndHandleCommand

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
    } // end switch command
} // end function handleStorageCommand

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
    } // end if saveDataToDisk == EXIT_FAILURE

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
    free( fileName );
} // end function saveDataToDiskHandler

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
    } // end if loadDataFromDisk == EXIT_FAILURE

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
    free( fileName );
} // end function loadDataFromDiskHandler

void saveDataToTapeHandler( void )
{
    showCommandHintInStatusBar( "Storage", "Start the tape and press any key" );
    cgetc();
    printLoadingOnStatusBar();

    if ( seriliazeTableDataToTape() == EXIT_FAILURE )
    {
        showCommandHintInStatusBar( "Error", "Failed to write to tape           " );
        cgetc();    
    } // end if seriliazeTableDataToTape == EXIT_FAILURE

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
} // end function saveDataToTapeHandler

void loadDataFromTapeHandler( void )
{
    showCommandHintInStatusBar( "Storage", "Load From Tape" );
    printLoadingOnStatusBar();

    if ( deSerializeTableDataFromTape() == EXIT_FAILURE )
    {
        showCommandHintInStatusBar( "Error", "Failed to load from tape          " );
        cgetc();    
    } // end if deSerializeTableDataFromTape == EXIT_FAILURE

    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " ); 
} // end function loadDataFromTapeHandler

void handleClearCommand( size_t fieldWidth, size_t rowHeadersWidth )
{
    showCommandHintInStatusBar( "Clear", "Type Y to confirm" );
    char command = cgetc();
    if ( command == 'y' || command == 'Y' )
    {
        printLoadingOnStatusBar();
        clearAllCellsInSheet( fieldWidth, rowHeadersWidth );
    } // end if command == 'y' || command == 'Y'
   
    clearStatusBarCommandHint();
} // end function handleClearCommand