#include "MPCB.h"

unsigned int MPCB::idInc = 0;

MPCB::MPCB(uint8_t *plStrt, unsigned int plSz)
{
  id = idInc;
  start = plStrt;
  size = plSz;
  isFree = new bool[size];
  for (unsigned int i = 0 ; i < size ; i++ )
  {
    isFree[i] = true;
  }
  subBlocks = new vector<MPCB*>;

  idInc++;
/* heap = new uint8_t[hpSz];
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
*/
}

MPCB::~MPCB()
{
  delete heap;
  delete isFree;
  delete subBlocks;
}



uint8_t* MPCB::allocate(unsigned int spaceSize)
{
  unsigned int freeStart = -1;
  bool checkMode = false;
  bool checkCounter = 0;
  bool success = false;
  // First part: Find free memory space large enough to fit spaceSize
  for (unsigned int i = 0 ; i < size ; i++)
  {
    if (isFree[i])
    {
      if (!checkMode)
      {
        freeStart = i;
        checkMode = true;
        checkCounter = 0;
      }
      if (checkCounter < spaceSize)
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

  for (unsigned int i = freeStart ; i < freeStart + spaceSize ; i++)
  {
    isFree[i] = false;
  }

  return &heap[freeStart]; //return location of start of MPool
}
#endif


uint8_t* MPCB::deallocate(unsigned int ident)
{
  unsigned int freeStart;
  MPCB* toRemove = findSubBlock(ident);
  freeStart = (unsigned int)(toRemove->getStart() - start);
  for (i = freeStart ; i < freeStart + toRemove->getSize() ; i++)
  {
    isFree[i] = true;
  }

  return &isFree[freeStart];
}


MPCB* MPCB::findSubBlock(unsigned int ident)
{
  for (vector<MPCB*>::iterator itr = subBlocks->begin() ; itr != subBlocks->end() ; itr++)
  {
    if ((*itr)->getID() == ident)
    {
      return *itr;
    }
  }
  return NULL;
}


void MPCB::insertSubBlock(MPCB* m)
{
  subBlocks->push_back(m);
}


void MPCB::removeSubBlock(unsigned int ident)
{
  for (vector<MPCB*>::iterator itr = subBlocks->begin() ; itr != subBlocks->end() ; itr++)
  {
    if ((*itr)->getID() == ident)
    {
      subBlocks->erase(itr);
      break;
    }
  }
}


unsigned int getID()
{
  return id;
}


uint8_t* getStart()
{
  return start;
}


unsigned int getSize()
{
  return size;
}


bool checkFree(unsigned int index)
{
  return isFree[index];
}

