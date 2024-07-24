#ifndef ADT_CELL_H
#define ADT_CELL_H

typedef struct Cell 
{
    char * type;
    void ( * print ) ( struct Cell * );
} Cell;


#endif // ADT_CELL_H