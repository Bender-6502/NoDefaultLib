#pragma once
#include "BasicStringFunctionsImpl.h"

namespace MiniCRT
{
  template <class charT>
  inline size_t StringLength(const charT* str)
  {
    if (!str)
      return 0;

    size_t length = 0;

    while (str[length] != '\0')
    {
      ++length;
    }

    return length;
  }

  template <class charT>
  inline const charT* StringCopy(charT* dest, size_t destLength, const charT* src, size_t srcLength)
  {
    if (auto result = static_cast<charT*>(Impl::StringCopy(dest, destLength, src, srcLength, sizeof(charT))); result != nullptr)
    {
      result[srcLength] = 0;
      return result;
    }
    return nullptr;
  }

  template <class charT>
  inline bool StringCompare(const charT* lhs, size_t lhsLength, const charT* rhs, size_t rhsLength)
  {
    if (!lhs || !rhs || lhsLength != rhsLength)
      return false;

    for (size_t i = 0; i < rhsLength; ++i)
    {
      if (lhs[i] != rhs[i])
        return false;
    }

    return true;
  }
}
