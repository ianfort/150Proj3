#ifndef M_POOL_H
#define M_POOL_H

class MPool
{
  uint8_t *heap;
  bool *isFree;
  unsigned int heapsz;
  unsigned int sharedsz;
public:
  MPool(unsigned int hpSz, unsigned int shSz);
  ~MPool();
  unsigned int assignMP(unsigned int stackSize);
};


#endif

