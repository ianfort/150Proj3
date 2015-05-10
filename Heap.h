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


#endif

