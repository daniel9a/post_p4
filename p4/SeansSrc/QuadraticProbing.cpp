#include "QuadraticProbing.h"

QuadraticHashTable::QuadraticHashTable(int sz)
  : size(sz) 
{
  array = new DiskInfo[size]; 
}

void QuadraticHashTable::insert( const DiskInfo & x )
{
  int currentPos = x.blockID % size;

  while( array[ currentPos ].blockID > 1 && array[ currentPos ].blockID != x.blockID )
    if(++currentPos == size)
      currentPos = 0;

  array[ currentPos ] = x;
}


void QuadraticHashTable::remove( const DiskInfo & x )
{
  int currentPos = x.blockID % size;

  while( array[ currentPos ].blockID != 0 && array[ currentPos ].blockID != x.blockID )
    if(++currentPos == size)
      currentPos = 0;
    
   
   if(array[ currentPos ].blockID == x.blockID)
     array[ currentPos ].blockID = 1;
}

DiskInfo & QuadraticHashTable::find( const DiskInfo & x ) 
{
   int currentPos = x.blockID % size;
  while( array[ currentPos ].blockID != 0 && array[ currentPos ].blockID != x.blockID )
    if(++currentPos == size)
      currentPos = 0;

  if (array[ currentPos ].blockID == x.blockID)
    return array[currentPos];
  else
    return ITEM_NOT_FOUND;
}


