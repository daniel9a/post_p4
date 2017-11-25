// Author Sean Davis
#ifndef defragmenterH
  #define defragmenterH

#include "DefragRunner.h"
#include "QuadraticProbing.h"

const int diskBlockPtr_SIZE = 11000;
#define HASH_SIZE 250000
class Defragmenter
{
  QuadraticHashTable hashTable;
  DiskBlock *diskBlockPtrs[diskBlockPtr_SIZE];
  unsigned short ptrStack[diskBlockPtr_SIZE];
  int ptrStackTop;
  int lastEmpty;
  DiskDrive *drivePtr;
  int currentBlockLoc;
  void initialize();
  DiskBlock* retrieve(int fileBlockID);
  void store(DiskBlock *diskBlockPtr, int currentBlockLoc);
public:
  Defragmenter(DiskDrive *diskDrive);

}; // class Defragmenter
#endif
