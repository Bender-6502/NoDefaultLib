#pragma once

namespace MiniCRT
{
  namespace Impl 
  {
    /// <summary>
    /// Allocate some memory on the heap. 
    /// The length is the number of elements to allocate, and typeSize is the size of each element.
    /// The total number of bytes allocated is length * typeSize.
    /// </summary>
    /// <param name="length"></param>
    /// <param name="typeSize"></param>
    /// <returns></returns>
    void* Allocate(size_t length, size_t typeSize);

    /// <summary>
    /// Deallocate memory from the heap previously allocated with Allocate.
    /// </summary>
    /// <param name="ptr"></param>
    void Deallocate(void* ptr);
  }
}
