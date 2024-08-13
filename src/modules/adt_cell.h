#ifndef ADT_CELL_H
#define ADT_CELL_H

typedef enum 
{
    BLANK_CELL,
    NUMBER_CELL,
    TEXT_CELL,
    UNKNOWN_CELL
} CellType;

typedef struct Cell 
{
    CellType type;
    void ( * print ) ( struct Cell * );

    union 
    {
        double number;
        char * text;
    } data;
} Cell;

Cell * Cell_createBlank();
Cell * Cell_createNumber( double number );
Cell * Cell_createText( char * text );
void Cell_printBlank( Cell * cell );
void Cell_printNumber( Cell * cell );
void Cell_printText( Cell * cell );

#endif // ADT_CELL_H