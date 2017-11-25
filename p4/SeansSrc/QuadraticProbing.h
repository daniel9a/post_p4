#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

class DiskInfo
{
public:
  int blockID;
  int currentLocation;  // negative indicates in List.
  DiskInfo(int bID = 0, int cL = 0) : blockID(bID), currentLocation(cL) {}
};

class QuadraticHashTable
{
  public:
    int count;
    explicit QuadraticHashTable(int siz);
    DiskInfo & find( const DiskInfo & x );
    void insert( const DiskInfo & x );
    void remove( const DiskInfo & x );
    DiskInfo *array;
    int size;
   // int rehashSize;
   // int currentSize;
    DiskInfo ITEM_NOT_FOUND;
};

#endif
