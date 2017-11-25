#include <iostream>
#include "QuadraticProbing.h"
#include "mynew.h"
using namespace std;



QuadraticHashTable::QuadraticHashTable(int sz ) : size(sz), currentSize(0)
{
  array = new BlockLoc[size];
  maxSize = 0;
}

void QuadraticHashTable::insert( const BlockLoc & x )
{
  int currentPos = x.origLoc % size;

  while(array[currentPos].origLoc > 1 && array[currentPos].origLoc != x.origLoc )
   if(++currentPos == size)
     currentPos = 0;

  if(array[currentPos].origLoc == 0)
  {
    ++currentSize;
    
    if(currentSize > maxSize)
      maxSize = currentSize;
  }  // if insert into empty space
  
  array[ currentPos ] = x;
  
 } // insert


/**
 * Remove item x from the hash table.
 */

int QuadraticHashTable::remove( int origLoc)
{
  int currentPos = origLoc % size;

  while( array[currentPos].origLoc > 0 && array[currentPos].origLoc != origLoc )
    if(++currentPos == size)
     currentPos = 0;
  
  if (array[currentPos].origLoc == origLoc)
  {
    array[currentPos].origLoc = 1;  // mark as deleted
    return array[currentPos].newLoc;
    --currentSize;
  }
  
  return 1;
}  //remove
