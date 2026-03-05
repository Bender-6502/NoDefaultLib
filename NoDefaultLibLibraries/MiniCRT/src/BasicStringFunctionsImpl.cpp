#pragma optimize("", off)
#include "BasicStringFunctionsImpl.h"

namespace MiniCRT
{
  namespace Impl
  {
    void* StringCopy(void* dest, size_t destLength, const void* src, size_t srcLength, size_t typeSize)
    {
      if (!dest || !src || destLength < srcLength)
        return nullptr;

      for (size_t i = 0; i < srcLength * typeSize; ++i)
      {
        static_cast<char*>(dest)[i] = static_cast<const char*>(src)[i];
      }

      return dest;
    }

  }
}

#pragma optimize("", on)
