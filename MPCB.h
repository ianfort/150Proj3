#ifndef MPCB_H
#define MPCB_H

#include <vector>
#include <stdint.h>
#include <cstddef>

//#define MEMHEAP 0
//#define MEMPOOL 1
//#define MEMBLOCK 2

/*
#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include <cstddef>

using namespace std;

class Heap
{
  uint8_t *heap;
  bool *isFree;
  unsigned int heapsz;
  unsigned int sharedsz;
public:
  Heap(unsigned int hpSz, unsigned int shSz);
  ~Heap();
  uint8_t* allocatePool(unsigned int stackSize);
};
*/

// enum MemLevel {MEMHEAP, MEMPOOL, MEMBLOCK};
 
using namespace std;

class MPCB
{
  static unsigned int idInc;
  unsigned int id;
  uint8_t *start;
  unsigned int size;
  bool *isFree;
//  MemLevel level;
  
  vector<MPCB*> *subBlocks;
public:
  MPCB(uint8_t *plStrt, unsigned int plSz /*, MemLevel lvl */);
  ~MPCB();

  uint8_t* allocate(unsigned int size);
  uint8_t* deallocate(unsigned int ident);

  MPCB* findSubBlock(unsigned int ident);
  void insertSubBlock(MPCB* m);
  void removeSubBlock(unsigned int ident);

  unsigned int getID();
  uint8_t* getStart();
  unsigned int getSize();
  bool checkFree(unsigned int index);
};

#endif
