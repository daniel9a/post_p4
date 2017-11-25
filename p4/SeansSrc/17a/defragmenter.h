// Author Sean Davis
#ifndef defragmenterH
  #define defragmenterH

#include "DefragRunner.h"
#include "QuadraticProbing.h"

const int diskBlockPtr_SIZE = 11000;
#define HASH_SIZE 250000

class FirstBlock
{
public:
  int oldLoc;
  int newLoc;
  int fileNum;
  FirstBlock(int oL = 0, int nL = 0, int fN = 0) : oldLoc(oL), newLoc(nL), fileNum(fN) {}
};
  

class Defragmenter
{
  QuadraticHashTable hashTable;
  DiskBlock *diskBlockPtrs[diskBlockPtr_SIZE];
  unsigned short ptrStack[diskBlockPtr_SIZE];
  int ptrStackTop;
  int lastEmpty;
  DiskDrive *drivePtr;
  int currentBlockLoc;
  FirstBlock contiguous[4000], random[4000];
  int contiguousCount, randomCount;
  void initialize();
  DiskBlock* retrieve(int fileBlockID);
  int store(DiskBlock *diskBlockPtr, int currentBlockLoc);
public:
  Defragmenter(DiskDrive *diskDrive);

}; // class Defragmenter
#endif
