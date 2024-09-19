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
    void ( * print ) ( struct Cell *, size_t  );

    union 
    {
        double number;
        char * text;
    } data;
} Cell;

Cell * Cell_createBlank();
Cell * Cell_createNumber( double number );
Cell * Cell_createText( char * text );
void Cell_printBlank( Cell * cell, size_t fieldWidth );
void Cell_printNumber( Cell * cell, size_t fieldWidth );
void Cell_printText( Cell * cell, size_t fieldWidth );

#endif // ADT_CELL_H