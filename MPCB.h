#ifndef MPCB_H
#define MPCB_H

#include <vector>
#include <stdint.h>
#include <cstddef>
#include <cassert>
#include <iostream>

#include "MemBlock.h"

//#define MEMHEAP 0
//#define MEMPOOL 1
//#define MEMBLOCK 2

// enum MemLevel {MEMHEAP, MEMPOOL, MEMBLOCK};
 
using namespace std;

class MPCB
{
  static unsigned int idInc;
  unsigned int id;
  uint8_t *start;
  unsigned int size;
  vector<MemBlock> *allocated;
//  bool *isFree;
//  MemLevel level;
  
//  vector<MPCB*> *subBlocks;
public:
  MPCB(uint8_t *plStrt, unsigned int plSz /*, MemLevel lvl */);
  ~MPCB();

  uint8_t* allocate(unsigned int size);
  bool deallocate(uint8_t* strt);

//  MPCB* findSubBlock(unsigned int ident);
//  void insertSubBlock(MPCB* m);
//  void removeSubBlock(unsigned int ident);

  unsigned int getID();
  uint8_t* getStart();
  unsigned int getSize();
  bool fullyFree();
  unsigned int countFree();
//  bool checkFree(unsigned int index);
};

#endif
