#pragma once

namespace MiniCRT
{
  namespace Impl 
  {
    /// <summary>
    /// Implementation of the StringCopy function that copies characters from 
    /// the source to the destination buffer. 
    /// 
    /// </summary>
    /// <param name="dest"></param>
    /// <param name="destLength"></param>
    /// <param name="src"></param>
    /// <param name="srcLength"></param>
    /// <param name="typeSize"></param>
    /// <returns></returns>
    void* StringCopy(void* dest, size_t destLength, const void* src, size_t srcLength, size_t typeSize);
  }
}
