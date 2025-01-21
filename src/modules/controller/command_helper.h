#ifndef COMMAND_HELPER_H
#define COMMAND_HELPER_H

#include <stdint.h>
#include <stdbool.h>

void handleKeyPress( char key,  size_t * xCursorPosition, size_t * yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );
void handleDownKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth );
void handleUpKey( size_t * yCursorPosition, size_t xCursorPosition, size_t rowHeadersWidth, size_t fieldWidth );
void handleRightKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );
void handleLeftKey( size_t * xCursorPosition, size_t yCursorPosition, size_t fieldWidth, size_t rowHeadersWidth );
void handleDeleteCell( void );
bool rightScroolCheck( size_t x, size_t y );
bool leftScroolCheck( size_t x, size_t y );
bool upScroolCheck( size_t x, size_t y );
bool downScroolCheck( size_t x, size_t y );


#endif // COMMAND_HELPER_H