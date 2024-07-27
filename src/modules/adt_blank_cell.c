#include <stdlib.h>

#include "adt_blank_cell.h"

void BlankCell_print( Cell * cell ) 
{
    
}

BlankCell * BlankCell_create() 
{
    BlankCell * cell = ( BlankCell * )malloc( sizeof( BlankCell ) );
    cell->base.type = "BlankCell";
    cell->base.print = BlankCell_print;
    
    return cell;
}