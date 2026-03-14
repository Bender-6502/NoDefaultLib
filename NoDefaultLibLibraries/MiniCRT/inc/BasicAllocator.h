#pragma once
#include "BasicAllocatorImpl.h"

namespace MiniCRT
{
  template <class T>
  class BasicAllocator
  {
  public:

    /// <summary>
    /// Allocate some memory on the heap. 
    /// <param name="length"></param>
    /// <returns></returns>
    static T* Allocate(size_t length)
    {
      return static_cast<T*>(Impl::Allocate(length, sizeof(T)));
    }

    /// <summary>
    /// Deallocate memory from the heap previously allocated with Allocate.
    /// </summary>
    static void Deallocate(T* ptr)
    {
      Impl::Deallocate(ptr);
    }
  };
}
