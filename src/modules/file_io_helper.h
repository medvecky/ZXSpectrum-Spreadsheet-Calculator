#ifndef FILE_IO_HELPER_H
#define FILE_IO_HELPER_H

#define MAX_BUFFER_SIZE 100

int saveDataToDisk( char * fileName );
int loadDataFromDisk( char * fileName );
int serializeTableDataToDisk( unsigned char fout );
int deSerializeTableDataFromDisk( unsigned char fin );
int esxdosReadLine( unsigned char handle, char * buffer, int buffer_size );
void loadDataFromTape( void );
int seriliazeTableDataToTape( void );
int deSerializeTableDataFromTape( void );

#endif // FILE_IO_HELPER_H