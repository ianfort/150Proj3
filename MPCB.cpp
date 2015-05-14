#include "MPCB.h"

unsigned int MPCB::idInc = 0;

MPCB::MPCB(uint8_t *plStrt, unsigned int plSz)
{
  id = idInc;
  start = plStrt;
  size = plSz;
  //allocated = new vector<MemBlock>;
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
  delete allocated;
  delete subBlocks;
}


MPCB* MPCB::allocate(unsigned int spaceSize)
{
  uint8_t* candidateStart = start;
  vector<MPCB*>::iterator newBlockItr;
  
  if (subBlocks->empty())
  {
    if (spaceSize <= size)
    {
      newBlockItr = subBlocks->push_back(new MPCB(candidateStart, spaceSize));
      return *newBlockItr;
    } // If spaceSize is smaller or equal in size to the memory pool.
    return NULL;
  } // If no space allocated yet
  else
  {
    for (vector<MPCB*>::iterator itr = subBlocks->begin() ; itr != subBlocks->end() ; itr++)
    {
      assert(candidateStart <= (*itr)->getStart());
      if (spaceSize <= (unsigned int)((*itr)->getStart() - candidateStart))
      {
        newBlockItr = subBlocks->insert(itr, new MPCB(candidateStart, spaceSize));
        foundSpace = true;
        return *newBlockItr;
      }
      
      candidateStart = (*itr)->getStart() + (uint8_t*)((*itr)->getSize());
    }
  } // If there is memory already allocated
  
  if ( spaceSize <= (unsigned int)((start + (uint8_t)size) - candidateStart) )
  {
    newBlockItr = subBlocks->push_back(new MPCB(candidateStart, spaceSize));
    return *newBlockItr;
  }
  
  return NULL;
}


MPCB* MPCB::deallocate(uint8_t* strt)
{
  MPCB* retVal;
  for (vector<MPCB*>::iterator itr = subBlocks->begin() ; itr != subBlocks->end() ; itr++)
  {
    if ((*itr)->getStart() == strt)
    {
      retVal = *itr;
      subBlocks->erase(itr);
      return retVal;
    }
  }
  return NULL;
} // Note: Does not delete memory MPCB. MPCB cleanup handled in VirtualMachine.cpp


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


unsigned int MPCB::getID()
{
  return id;
}


uint8_t* MPCB::getStart()
{
  return start;
}


unsigned int MPCB::getSize()
{
  return size;
}

