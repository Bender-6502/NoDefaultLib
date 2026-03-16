#pragma once
#include "BasicString.h"

namespace MiniCRT
{
  using String  = BasicString<char>;
  using WString = BasicString<wchar_t>;

  inline String ToString(int val)
  {
    char buf[256];
    return Impl::IntToArray(val, buf, 10);
  }

  inline String ToString(unsigned int val)
  {
    char buf[256];
    return Impl::UnsignedIntToArray(val, buf, 10);
  }

  inline WString ToWString(int val)
  {
    wchar_t buf[256];
    return Impl::IntToArray(val, buf, 10);
  }

  inline WString ToWString(unsigned int val)
  {
    wchar_t buf[256];
    return Impl::UnsignedIntToArray(val, buf, 10);
  }
}
