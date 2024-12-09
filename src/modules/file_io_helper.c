#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <arch/zxn/esxdos.h>
#include <conio.h>

#include "file_io_helper.h"
#include "system_helper.h"
#include "adt_sheet.h"

extern Sheet * sheet;

int saveDataToDisk( char * fileName )
{
    unsigned char fout = 0xff;
    
    fout = esx_f_open( fileName, ESX_MODE_OPEN_CREAT | ESX_MODE_RW );
    if ( fout == 0 )
    {
        return EXIT_FAILURE;
    }

    serializeTableDataToDisk( fout );

    esx_f_close( fout );
    return EXIT_SUCCESS;
}

int serializeTableDataToDisk( unsigned char fout )
{
    char outStringBuffer[ MAX_BUFFER_SIZE ];
    for ( size_t row = 0; row < NUMBER_OF_ROWS; row++ ) 
    {
        for ( size_t column = 0; column < NUMBER_OF_COLUMNS; column++) 
        {
            Cell * cell = sheet->cells[ row ][ column ];
            size_t stringSize = 0;
            size_t bytesWRitten = 0;
            
            if ( cell != NULL ) 
            {
                if ( cell->type == NUMBER_CELL ) 
                {
                    stringSize = snprintf( 
                        outStringBuffer, 
                        sizeof( outStringBuffer ), 
                        "%zu,%zu,N,%f\n", 
                        row,
                        column, 
                        cell->data.number );
                } 
                else if ( cell->type == TEXT_CELL ) 
                {
                    stringSize = snprintf( 
                        outStringBuffer, 
                        sizeof( outStringBuffer ),
                        "%zu,%zu,T,%s\n",
                        row, 
                        column,
                        cell->data.text );
                }

                bytesWRitten = esx_f_write( fout, outStringBuffer, stringSize );
                if ( bytesWRitten != stringSize ) 
                {
                     esx_f_close( fout );
                     return EXIT_FAILURE;
                }
            }
        }
    }
}

int loadDataFromDisk( char * fileName )
{
    unsigned char fin = 0xff;
    if ( ( fin = esx_f_open( fileName, ESX_MODE_OPEN_EXIST | ESX_MODE_R ) ) == 0xff )
    {
        return EXIT_FAILURE;
    }

    deSerializeTableDataToDisk( fin );

    esx_f_close( fin );
    return EXIT_SUCCESS;
}

int deSerializeTableDataToDisk( unsigned char fin )
{
    char buffer[ MAX_BUFFER_SIZE ];
    while ( esxdosReadLine( fin, buffer, sizeof( buffer ) ) > 0 )
    {
        size_t row, col;
        char type;
        char data[ MAX_BUFFER_SIZE ];

        if ( ( sscanf( buffer, "%u,%u,%c,%s", &row, &col, &type, &data ) ) == 4 ) 
        {
            if ( type == 'N' ) 
            {
                double number = atof( data );
                Sheet_setCell( sheet, row, col, Cell_createNumber( number ) );
            } 
            else if ( type == 'T' ) 
            {
                Sheet_setCell( sheet, row, col, Cell_createText( strdup( data ) ) );
            }
        }
    }

    return EXIT_SUCCESS;
}

int esxdosReadLine( unsigned char handle, char * buffer, int buffer_size ) 
{
    unsigned char byte;
    int bytes_read = 0;

    while ( bytes_read < buffer_size - 1 ) 
    { 
        if ( esxdos_f_read( handle, &byte, 1 ) == 0 ) 
        {
            if ( bytes_read == 0 ) 
            {
                return 0; 
            }
            break;
        }

        if ( byte == '\n' ) 
        {
            break; 
        }

        buffer[ bytes_read++ ] = byte;
    }

    buffer[ bytes_read ] = '\0'; 
    
    return bytes_read; 
}

void loadDataFromTape( void )
{
    char name[ 11 ]; 
    char data[ 100 ];
    size_t load_address = (size_t)data;
    size_t length = 100;

    tape_load_block(load_address, length, 0xff);

    gotoxy( 0, 2 );
    printf( "Data[%s]", data );
    cgetc();
}

int calculateBufferSize( void )
{
    uint16_t bufferSize = 0;
    for ( size_t row = 0; row < NUMBER_OF_ROWS; row++ )
    {
        for ( size_t column = 0; column < NUMBER_OF_COLUMNS; column++ )
        {
            Cell * cell = sheet->cells[ row ][ column ];
            if ( cell != NULL )
            {
                if ( cell->type == NUMBER_CELL )
                {
                    bufferSize += snprintf( NULL, 0, "%zu,%zu,N,%f\n", row, column, cell->data.number );
                }
                else if ( cell->type == TEXT_CELL )
                {
                    bufferSize += snprintf( NULL, 0, "%zu,%zu,T,%s\n", row, column, cell->data.text );
                }
            }
        }
    }
    
    return bufferSize + 1;
}

int seriliazeTableDataToTape( void )
{
    char name[ 11 ] = "SheetData";
    uint16_t bufferSize = calculateBufferSize();
    char * outStringBuffer = ( char * )malloc( bufferSize );
    if ( outStringBuffer == NULL )
    {
        gotoxy( 0, 2 );
        puts( "Failed to allocate memory" );
        cgetc();
        return EXIT_FAILURE;
    }
    size_t bufferOffset = 0;

    for ( size_t row = 0; row < NUMBER_OF_ROWS; row++ )
    {
        for ( size_t column = 0; column < NUMBER_OF_COLUMNS; column++ )
        {
            Cell *cell = sheet->cells[ row ][ column ];
            size_t stringSize = 0;

            if ( cell != NULL )
            {
                if ( cell->type == NUMBER_CELL )
                {
                    stringSize = snprintf(
                        outStringBuffer + bufferOffset,
                        bufferSize - bufferOffset,
                        "%zu,%zu,N,%f\n",
                        row,
                        column,
                        cell->data.number );
                }
                else if ( cell->type == TEXT_CELL )
                {
                    stringSize = snprintf(
                        outStringBuffer + bufferOffset,
                        bufferSize - bufferOffset,
                        "%zu,%zu,T,%s\n",
                        row,
                        column,
                        cell->data.text );
                }

                bufferOffset += stringSize;
                if ( bufferOffset >= bufferSize )
                {
                    free( outStringBuffer );
                    return EXIT_FAILURE;
                }
            }
        }
    }

    tape_save( name, (size_t)outStringBuffer, (void *)outStringBuffer, bufferOffset );

    free( outStringBuffer );

    return EXIT_SUCCESS;
}