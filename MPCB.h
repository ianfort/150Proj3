#ifndef MPCB_H
#define MPCB_H

#include "Heap.h"

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

class MPCB
{
  static unsigned int idInc;
  unsigned int id;
  uint8_t *start;
  unsigned int size;
  bool *isFree;

public:
  MPCB(unsigned int ident, uint8_t *pStrt, unsigned int plSz);
  ~MPCB();

  uint8_t* allocateMem(unsigned int size);
  void deallocateMem()
};

#endif
