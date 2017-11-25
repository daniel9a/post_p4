// Author Sean Davis
#ifndef defragmenterH
  #define defragmenterH
#include "QuadraticProbing.h"
#include "DefragRunner.h"

#define HASH_SIZE 200000
//#define REHASH_SIZE 185000
#define LIST_SIZE 11700

class Defragmenter
{
  QuadraticHashTable hashTable;
  DiskBlock* list[LIST_SIZE];
  int stack[LIST_SIZE];
  DiskDrive *diskDrive;
  
  int listCount;
  int currentPos;
  int lastEmpty;
  int topIndex;
  int freeCount;
  DiskBlock* getSrcBlock(int srcID);
  void moveFile(DirectoryEntry &entry);
  void store(int blockID);
public:
  Defragmenter(DiskDrive *diskDrive);

}; // class Defragmenter
#endif
