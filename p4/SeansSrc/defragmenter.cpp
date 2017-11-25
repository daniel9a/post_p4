#include "defragmenter.h"
#include "DefragRunner.h"
#include "QuadraticProbing.h"

 Defragmenter::Defragmenter(DiskDrive *diskDriv) : hashTable(HASH_SIZE), 
   diskDrive(diskDriv), listCount(1),currentPos(2), topIndex(0)
 {
   for(lastEmpty = diskDrive->getCapacity() - 1; diskDrive->FAT[lastEmpty]; lastEmpty--);
   
   for(int i = 0; i < diskDrive->getNumFiles(); i++)
     moveFile(diskDrive->directory[i]);
   
  // cout << "HASH_SIZE: " << HASH_SIZE << " LIST_SIZE: " << LIST_SIZE <<  " REHASH_SIZE: " << REHASH_SIZE << endl; 
  // cout << "Hash size: " << hashTable.currentSize << endl;
 }  // Defragmenter
 
 void Defragmenter::moveFile(DirectoryEntry &entry)
 {
   int srcID = entry.getFirstBlockID(), nextID;
   entry.setFirstBlockID(currentPos);
   
   while(srcID != 1)
   {
     DiskBlock *tempBlock = getSrcBlock(srcID);
     nextID = tempBlock->getNext();
     
     if(srcID != currentPos)
     {
       if(diskDrive->FAT[currentPos]) // if not empty
         store(currentPos);
       
       tempBlock->setNext(currentPos + 1);
       diskDrive->writeDiskBlock(tempBlock, currentPos);
       diskDrive->FAT[currentPos] = 1;
     }  // if source and destination not the same.
     else  // from the same position
     {
       if(nextID != currentPos + 1)
       {
         tempBlock->setNext(currentPos + 1);
         diskDrive->writeDiskBlock(tempBlock, currentPos);
         diskDrive->FAT[currentPos] = 1;
       }  // if next pointer is not pointing at the next block position
     }
     
     delete tempBlock;
     srcID = nextID;
     currentPos++;
   }  // for each file block 
   
 }// moveFile()
 
 
 DiskBlock* Defragmenter::getSrcBlock(int srcID)
 {
   DiskBlock *tempBlock;
   DiskInfo diskInfo2, diskInfo = hashTable.find(DiskInfo(srcID));
   
   if(diskInfo.currentLocation == 0)  // not in hashTable
   {
     tempBlock = diskDrive->readDiskBlock(srcID);
     diskDrive->FAT[srcID] = 0;
     if(srcID > lastEmpty)
       lastEmpty = srcID;
   }
   else  // in hashTable
   {
     while(diskInfo.currentLocation > 0 
       && (hashTable.find(DiskInfo(diskInfo.currentLocation))).currentLocation != 0)
     {
       hashTable.remove(diskInfo);
       diskInfo = hashTable.find(DiskInfo(diskInfo.currentLocation));
     }  // while another link to srcID block.
     
     hashTable.remove(diskInfo);
      
     if(diskInfo.currentLocation < 0) // if in list
     {
       tempBlock = list[-diskInfo.currentLocation];
       stack[topIndex++] = -diskInfo.currentLocation;
     }
     else  // not in list so somewhere on disk
     {
       tempBlock = diskDrive->readDiskBlock(diskInfo.currentLocation);
      diskDrive->FAT[diskInfo.currentLocation] = 0;
       
      if(diskInfo.currentLocation > lastEmpty)
        lastEmpty = diskInfo.currentLocation;
     }
    }  // in HashTable

   return tempBlock;
 } // getSrcBlock()
   
 
 void Defragmenter::store(int blockID)
 {
   DiskBlock *tempBlock = diskDrive->readDiskBlock(blockID);
   diskDrive->FAT[blockID] = 0;
   
   int listIndex;
   
   if(listCount < LIST_SIZE  || topIndex > 0)
   {
     if(topIndex > 0) // use from within current list size
       listIndex = stack[--topIndex];
     else // must add to end of list
       listIndex = listCount++;
    
     list[listIndex] = tempBlock;
     hashTable.insert(DiskInfo(blockID, -listIndex));
   }  // if room in list
   else  // must store on the drive
   {
     diskDrive->writeDiskBlock(tempBlock, lastEmpty);
     diskDrive->FAT[lastEmpty] = 1;
     hashTable.insert(DiskInfo(blockID,lastEmpty));
     delete tempBlock;
     for(; diskDrive->FAT[lastEmpty]; lastEmpty--);
   }  // else storing on the drive
   
 }  // store()
 
