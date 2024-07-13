#include <conio.h>


void setUpScreen( void )
{
    bordercolor( BLACK );
    textcolor( YELLOW );
    textbackground( BLACK );
    clrscr();
}

void restoreScreen( void )
{
    bordercolor( WHITE );
    textcolor( BLACK );
    textbackground( WHITE );
    clrscr();
}

void inverseAttributes( void )
{
    textcolor( BLACK );
    textbackground( YELLOW );
}

void restoreAttributes( void )
{
    textcolor(YELLOW );
    textbackground( BLACK );
}