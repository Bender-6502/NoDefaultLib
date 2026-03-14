#pragma once
#include "BasicFileStream.h"
#include "BasicString.h"

namespace MiniCRT
{
  using FileStream  = BasicFileStream<char>;
  using WFileStream = BasicFileStream<wchar_t>;

  BasicFileStream<char>& Getline(BasicFileStream<char>& is, BasicString<char>& str)
  {
    while (!is.Eof())
    {
      char c = 0;
      is.Get(c);
      if (c == '\r')
        continue;
      if (c == '\n')
        break;
      str += c;
    }
    return is;
  }

  BasicFileStream<wchar_t>& Getline(BasicFileStream<wchar_t>& is, BasicString<wchar_t>& str)
  {
    while (!is.Eof())
    {
      wchar_t c = 0;
      is.Get(c);
      if (c == '\r')
        continue;
      if (c == '\n')
        break;
      str += c;
    }
    return is;
  }
}
