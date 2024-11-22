#ifndef COMMAND_TOKEN_HELPER_H
#define COMMAND_TOKEN_HELPER_H

void handleCommandToken( void );
void showCommandHintInStatusBar( char * categoryHint, char * commandHint );
void getAndHandleCommand( void );
void handleStorageCommand( void );
void clearStatusBarCommandHint( void );
void saveDataToDiskHandler( void );

#endif // COMMAND_TOKEN_HELPER_H