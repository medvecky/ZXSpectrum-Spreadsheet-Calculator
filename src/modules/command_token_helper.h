#ifndef COMMAND_TOKEN_HELPER_H
#define COMMAND_TOKEN_HELPER_H

void handleCommandToken( size_t fieldWidth, size_t rowHeadersWidth );
void showCommandHintInStatusBar( char * categoryHint, char * commandHint );
void getAndHandleCommand( size_t fieldWidth, size_t rowHeadersWidth );
void handleStorageCommand( size_t fieldWidth, size_t rowHeadersWidth );
void clearStatusBarCommandHint( void );
void saveDataToDiskHandler( void );
void loadDataFromDiskHandler( void );

#endif // COMMAND_TOKEN_HELPER_H