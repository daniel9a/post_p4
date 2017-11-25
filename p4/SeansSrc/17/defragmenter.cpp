#include "defragmenter.h"
#include "mynew.h"
#include "DefragRunner.h"
#include <cstdlib>  // for abs

extern int maxRAM;



Defragmenter::Defragmenter(DiskDrive *diskDrive) : hashTable(HASH_SIZE), 
  drivePtr(diskDrive), currentBlockLoc(2)
{
  initialize();
  int fileBlockID, count, fileSize, count2 = 0;
  DiskBlock *diskBlockPtr;
  
  for(int fileNum = 0; fileNum < drivePtr->getNumFiles(); fileNum++)
  {
   // cout << fileNum << endl;
    fileSize = drivePtr->directory[fileNum].getSize();
    fileBlockID = drivePtr->directory[fileNum].getFirstBlockID();
    drivePtr->directory[fileNum].setFirstBlockID(currentBlockLoc);
    
    for(count = 0; count < fileSize; count++, currentBlockLoc++)
    {
      if(drivePtr->FAT[currentBlockLoc])
      {
        diskBlockPtr = drivePtr->readDiskBlock(currentBlockLoc);
        store(diskBlockPtr, currentBlockLoc);
      }  // currentBlockLoc not empty
      
      diskBlockPtr = retrieve(fileBlockID);
      fileBlockID = diskBlockPtr->getNext();
    
      if(fileBlockID > 1) // if not at end of file
        diskBlockPtr->setNext(currentBlockLoc + 1);
      
      drivePtr->writeDiskBlock(diskBlockPtr, currentBlockLoc);
      drivePtr->FAT[currentBlockLoc] = true;
      delete diskBlockPtr;
    } // for each file block;
  } // for each file
  
  cout << "Max size: " << hashTable.maxSize << endl;
}  // Defragmenter()
  


void Defragmenter::initialize()
{
  for(ptrStackTop = 0; ptrStackTop < diskBlockPtr_SIZE - 1; ptrStackTop++)
    ptrStack[ptrStackTop] = ptrStackTop;  
  
  ptrStackTop--;
  
  lastEmpty = drivePtr->getCapacity() - 1;
}  // initialize()


DiskBlock* Defragmenter::retrieve(int fileBlockID)
{
  DiskBlock *diskBlockPtr;
  int newLoc2, newLoc = hashTable.remove(fileBlockID);
  
  if(newLoc == 1) // not found in known storage
  {
     diskBlockPtr = drivePtr->readDiskBlock(fileBlockID);
     drivePtr->FAT[fileBlockID] = false;
     
     if(fileBlockID > lastEmpty)
       lastEmpty = fileBlockID;
  }
  else // in storage
  {
    while(newLoc > 0) // not in diskBlockPtrs RAM storage 
    {  
      newLoc2 = hashTable.remove(newLoc); 
      
      if(newLoc2 == 1)  // 1 is sentinel indicating not found
        break;  
    
      newLoc = newLoc2;
    }
    
    if(newLoc <= 0) // in diskBlockPtrs RAM storage 
    {
      diskBlockPtr = diskBlockPtrs[-newLoc];
      ptrStack[++ptrStackTop] = -newLoc;
    } // if in RAM storage
    else  // moved on disk
    {
      diskBlockPtr = drivePtr->readDiskBlock(newLoc);
      drivePtr->FAT[newLoc] = false;

      if(newLoc > lastEmpty)
        lastEmpty = newLoc;
    }
  } // else in storage
        
  return diskBlockPtr;
} // retrieve()


void Defragmenter::store(DiskBlock *diskBlockPtr, int blockID)
{
  if(ptrStackTop > -1) // if room in the array of pointers so non-positive
  {
    diskBlockPtrs[ptrStack[ptrStackTop]] = diskBlockPtr;
    hashTable.insert(BlockLoc(blockID, -ptrStack[ptrStackTop--]));
  }  // if room in RAM array
  else  // must store on disk, so > 2 
  {
    for(; drivePtr->FAT[lastEmpty]; lastEmpty--);
    drivePtr->writeDiskBlock(diskBlockPtr, lastEmpty);
    delete diskBlockPtr;
    hashTable.insert(BlockLoc(blockID, lastEmpty));
    drivePtr->FAT[lastEmpty--] = true;
  }  // else stored on disk
}  // store()



