#include "BasicAllocatorImpl.h"

#include <Windows.h>

namespace MiniCRT
{
  namespace Impl
  {
    void* Allocate(size_t length, size_t typeSize)
    {
      return ::HeapAlloc(::GetProcessHeap(), 0, length * typeSize);
    }

    void Deallocate(void* ptr)
    {
      if (ptr)
        ::HeapFree(::GetProcessHeap(), 0, ptr);
    }
  }
}