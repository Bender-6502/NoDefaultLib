#pragma once

namespace MiniCRT
{
  template <class T>
  class BasicListAllocator
  {
  public:

    /// <summary>
    /// Allocate some memory on the heap. 
    /// <param name="length"></param>
    /// <returns></returns>
    static T* Allocate()
    {
      return new T();
    }

    /// <summary>
    /// Deallocate memory from the heap previously allocated with Allocate.
    /// </summary>
    static void Deallocate(T* ptr)
    {
      delete ptr;
    }
  };
}
