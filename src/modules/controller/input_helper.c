#include <conio.h>
#include <math.h>
#include <ctype.h>

#include "input_helper.h"

#include "../model/adt_cell.h"
#include "../model/adt_sheet.h"

int handleInput( void )
{
    gotoxy( 0, 2 );
    Cell * cell = createCell();
    Sheet_setCell( sheet, yCellCoordinate, xCellCoordinate, cell );
    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
    
    return EXIT_SUCCESS;
} // end function handleInput 

Cell * createCell( void )
{
    Cell * cell = NULL;
    char * inputString = getInputString();

    if ( isNumber( inputString ) ) 
    {
        double number = atof( inputString );
        cell = Cell_createNumber( number );
    }
    else 
    {
        cell = Cell_createText( inputString );
    }

    return cell;
} // end function createCell

char * getInputString( void )
{
    char * inputString = ( char * )malloc( MAX_INPUT_LENGTH * sizeof( char ) );
    
    if ( inputString == NULL ) 
    {
        puts( "Memory allocation failed" );
        cgetc();
        
        return NULL;
    } // end if inputString == NULL
    
    if ( fgets( inputString, MAX_INPUT_LENGTH, stdin ) == NULL ) 
    {
        puts( "Error reading input" );
        free( inputString );
        cgetc();
    
        return NULL;
    } // end if fgets inputString MAX_INPUT_LENGTH stdin == NULL

    size_t len = strlen( inputString );
    
    if ( len > 0 && inputString[ len - 1 ] == '\n' ) 
    {
        inputString[ len - 1 ] = '\0';   
    } // end if len > 0 && inputString[ len - 1 ] == '\n'

    return inputString;
} // end function getInputString

bool isNumber( const char * str ) 
{
    size_t i = 0;

    for ( i = 0; str[ i ]; i++ ) 
    {
        if ( !isdigit( str[ i ] ) && str[ i ] != '-' && 
                str[ i ] != 'e' && str[ i ] != '.' ) 
        {
            return false;
        } // end if !isdigit str i && str i != - && str i != e && str i != .
    } // end for i < strlen str
    
    return true;
} // end function isNumber