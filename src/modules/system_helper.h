#ifndef _SYSTEM_HELPER_H_
#define _SYSTEM_HELPER_H_

void setUpScreen( void );
void restoreScreen( void );
void inverseAttributes( void );
void restoreAttributes( void );

#define SCREEN_HEIGHT       23
#define SCREEN_WIDTH        41
#define NUMBER_OF_ROWS      64
#define NUMBER_OF_COLUMNS   64 

#endif // _SYSTEM_HELPER_H_