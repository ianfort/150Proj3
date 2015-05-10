#include "Heap.h"

/*
class MPool
{
  uint8_t *heap;
  bool *isFree;
  unsigned int heapsz;
  unsigned int sharedsz;
public:
  MPool(unsigned int hpSz, unsigned int shSz);
  ~MPool();
};
*/

Heap::Heap(unsigned int hpSz, unsigned int shSz)
{
  heap = new uint8_t[hpSz];
  isFree = new bool[hpSz];
  for (unsigned int i = 0 ; i < shSz ; i++ )
  {
    isFree[i] = false;
  }
  for (unsigned int i = shSz ; i < hpSz ; i++ )
  {
    isFree[i] = true;
  }
  heapsz = hpSz;
  sharedsz = shSz;
}

Heap::~Heap()
{
  delete heap;
  delete isFree;
}


uint8_t* Heap::allocatePool(unsigned int stackSize)
{
  unsigned int freeStart = -1;
  bool checkMode = false;
  bool checkCounter = 0;
  bool success = false;
  // First part: Find free memory space large enough to fit stackSize
  for (unsigned int i = sharedsz ; i < heapsz ; i++)
  {
    if (isFree[i])
    {
      if (!checkMode)
      {
        freeStart = i;
        checkMode = true;
        checkCounter = 0;
      }
      if (checkCounter < stackSize)
      {
        checkCounter++;
      }
      else
      {
        success = true;
        break;
      }
    }
    else
    {
      checkMode = false;
    }
  }

  if (!success)
  {
    return NULL;
  }
  // Second part: Allocate memory space

  for (unsigned int i = freeStart ; i < freeStart + stackSize ; i++)
  {
    isFree[i] = false;
  }

  return &heap[freeStart]; //return location of start of MPool
}
