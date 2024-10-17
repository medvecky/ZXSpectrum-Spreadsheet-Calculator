#include <conio.h>
#include <math.h>
#include <ctype.h>

#include "input_helper.h"
#include "adt_cell.h"
#include "adt_sheet.h"

int handleInput( void )
{
    gotoxy( 0, 2 );
    Cell * cell = createCell();
    Sheet_setCell( sheet, yCellCoordinate, xCellCoordinate, cell );
    gotoxy( 0, 2 );
    printf( "%*s", SCREEN_WIDTH, " " );
    
    return EXIT_SUCCESS;
}

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
}

char * getInputString( void )
{
    char * inputString = ( char * )malloc( MAX_INPUT_LENGTH * sizeof( char ) );
    
    if ( inputString == NULL ) 
    {
        puts( "Memory allocation failed" );
        cgetc();
        
        return NULL;
    }
    
    if ( fgets( inputString, MAX_INPUT_LENGTH, stdin ) == NULL ) 
    {
        puts( "Error reading input" );
        free( inputString );
        cgetc();
    
        return NULL;
    }

    size_t len = strlen( inputString );
    
    if ( len > 0 && inputString[ len - 1 ] == '\n' ) 
    {
        inputString[ len - 1 ] = '\0';   
    }

    return inputString;
}

bool isNumber( const char * str ) 
{
    size_t i = 0;

    for ( i = 0; str[ i ]; i++ ) 
    {
        if ( !isdigit( str[ i ] ) && str[ i ] != '-' && 
                str[ i ] != 'e' && str[ i ] != '.' ) 
        {
            return false;
        }
    }
    
    return true;
}