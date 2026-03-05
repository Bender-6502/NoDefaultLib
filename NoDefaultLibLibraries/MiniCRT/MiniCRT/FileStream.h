#pragma once
#include "BasicFileStream.h"

namespace MiniCRT
{
  using FileStream  = BasicFileStream<char>;
  using WFileStream = BasicFileStream<wchar_t>;
}
