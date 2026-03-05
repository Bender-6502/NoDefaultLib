#pragma once

namespace MiniCRT
{
  namespace Impl 
  {
    void* StringCopy(void* dest, size_t destLength, const void* src, size_t srcLength, size_t typeSize);
  }
}
