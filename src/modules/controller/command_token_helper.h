#ifndef COMMAND_TOKEN_HELPER_H
#define COMMAND_TOKEN_HELPER_H

void handleCommandToken( size_t fieldWidth, size_t rowHeadersWidth );
void showCommandHintInStatusBar( char * categoryHint, char * commandHint );
void getAndHandleCommand( size_t fieldWidth, size_t rowHeadersWidth );
void handleStorageCommand( size_t fieldWidth, size_t rowHeadersWidth );
void clearStatusBarCommandHint( void );
void saveDataToDiskHandler( void );
void loadDataFromDiskHandler( void );
void saveDataToTapeHandler( void );
void loadDataFromTapeHandler( void );
void handleClearCommand( size_t fieldWidth, size_t rowHeadersWidth );

#endif // COMMAND_TOKEN_HELPER_H