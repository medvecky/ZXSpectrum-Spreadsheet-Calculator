#include <stdio.h>
#include <stdlib.h>
#include <arch/zxn/esxdos.h>

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