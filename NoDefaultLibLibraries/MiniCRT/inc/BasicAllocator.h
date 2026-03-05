#pragma once
#include "BasicAllocatorImpl.h"

namespace MiniCRT
{
  template <class charT>
  class BasicAllocator
  {
  public:

    /// <summary>
    /// Allocate some memory on the heap. 
    /// <param name="length"></param>
    /// <returns></returns>
    static charT* Allocate(size_t length)
    {
      return static_cast<charT*>(Impl::Allocate(length, sizeof(charT)));
    }

    /// <summary>
    /// Deallocate memory from the heap previously allocated with Allocate.
    /// </summary>
    static void Deallocate(charT* ptr)
    {
      Impl::Deallocate(ptr);
    }
  };
}
