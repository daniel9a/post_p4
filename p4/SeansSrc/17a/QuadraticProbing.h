#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

class BlockLoc
{
public:
  int origLoc;
  int newLoc;
  BlockLoc(int orig = 0, int newL = 0) : origLoc(orig), newLoc(newL) {}
};  // class BlockLoc


class QuadraticHashTable
{
  public:
    explicit QuadraticHashTable(int sz);
  //  const BlockLoc & find( const BlockLoc & x ) const;
    void makeEmpty( );
    void insert( const BlockLoc & x );
    int remove( int origLoc);
    int maxSize;
  private:
    BlockLoc *array;
    int size;
    int currentSize;
    int findPos( const BlockLoc & x ) const;
};

#endif
