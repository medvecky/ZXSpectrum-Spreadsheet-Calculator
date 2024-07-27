#include <stdio.h>

#include "adt_number_cell.h"

void NumberCell_print( Cell * cell ) 
{
    NumberCell * numCell = ( NumberCell * )cell;
    printf( "%lf", numCell->value) ;
}

NumberCell * NumberCell_create( double value ) 
{
    NumberCell * cell = ( NumberCell * )malloc( sizeof( NumberCell ) );
    cell->base.type = "NumberCell";
    cell->base.print = NumberCell_print;
    cell->value = value;
    
    return cell;
}