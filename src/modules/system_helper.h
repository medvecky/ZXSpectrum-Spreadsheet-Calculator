#ifndef _SYSTEM_HELPER_H_
#define _SYSTEM_HELPER_H_

void setUpScreen( void );
void restoreScreen( void );
void inverseAttributes( void );
void restoreAttributes( void );

#define SCREEN_HEIGHT  23
#define SCREEN_WIDTH   41
#define NUM_OF_ROWS    254

#endif // _SYSTEM_HELPER_H_