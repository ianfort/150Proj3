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

MPool::Mpool(unsigned int hpSz, unsigned int shSz)
{
  heap = new uint8_t[hpSz];
  isFree = new bool[hpSz];
  for (int i = 0 ; i < shSz ; i++ )
  {
    isFree = false;
  }
  for (int i = shSz ; i < hpSz ; i++ )
  {
    isFree = true;
  }
  heapsz = hpSz;
  sharedsz = shSz;
}

MPool::~MPool()
{
  delete heap;
  delete isFree;
}


unsigned int assignMP(unsigned int stackSize)
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

  for (int i = freeStart ; i < freeStart + stackSize ; i++)
  {
    isFree[i] = false;
  }

  return &heap[freeStart];
}
