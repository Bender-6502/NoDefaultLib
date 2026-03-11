#pragma once
#include "BasicStringFunctionsImpl.h"

namespace MiniCRT
{
  /// <summary>
  /// Returns the length of the specified null-terminated string, excluding the 
  /// null terminator. If the input pointer is null, the function returns 0.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="str"></param>
  /// <returns></returns>
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

  /// <summary>
  /// Copies the specified number of characters from the source string to the 
  /// destination buffer. The function ensures that the destination buffer is 
  /// null-terminated, 
  /// and does
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="dest"></param>
  /// <param name="destLength"></param>
  /// <param name="src"></param>
  /// <param name="srcLength"></param>
  /// <returns></returns>
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

  /// <summary>
  /// Compares two strings for equality. The function returns true if the 
  /// two strings are equal, and false otherwise. The function considers two 
  /// strings to be equal if they have the same length and the same characters 
  /// in the same order. If either of the input pointers is null, or if the 
  /// lengths of the two strings are different, the function returns false.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="lhs"></param>
  /// <param name="lhsLength"></param>
  /// <param name="rhs"></param>
  /// <param name="rhsLength"></param>
  /// <returns></returns>
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
