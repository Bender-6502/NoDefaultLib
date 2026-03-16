#pragma once

namespace MiniCRT
{
  template <class charT>
  class BasicStringAllocator
  {
  public:
    /// <summary>
    /// Allocate some memory on the heap. 
    /// <param name="length"></param>
    /// <returns></returns>
    static charT* Allocate(size_t length)
    {
      return new charT[length];
    }

    /// <summary>
    /// Deallocate memory from the heap previously allocated with Allocate.
    /// </summary>
    static void Deallocate(charT* ptr)
    {
      delete[] ptr;
    }
  };
}
