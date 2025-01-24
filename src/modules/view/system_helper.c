#include <conio.h>


void setUpScreen( void )
{
    bordercolor( BLACK );
    textcolor( YELLOW );
    textbackground( BLACK );
    clrscr();
} // end function setUpScreen

void restoreScreen( void )
{
    bordercolor( WHITE );
    textcolor( BLACK );
    textbackground( WHITE );
    clrscr();
} // end function restoreScreen

void inverseAttributes( void )
{
    textcolor( BLACK );
    textbackground( YELLOW );
} // end function inverseAttributes

void restoreAttributes( void )
{
    textcolor( YELLOW );
    textbackground( BLACK );
} // end function restoreAttributes