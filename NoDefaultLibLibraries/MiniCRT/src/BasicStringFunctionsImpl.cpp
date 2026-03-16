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

    const char* IntToArray(int i, char* s, int rad)
    {
      auto t = i;
      auto r = s;
      char symbols[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

      if (i < 0)
      {
        i = -i;
        *s++ = '-';
      }
      do
      {
        ++s;
      } while (t /= rad);
      *s = '\0';
      do
      {
        *--s = symbols[i % rad];
      } while (i /= rad);
      return r;
    }

    const wchar_t* IntToArray(int i, wchar_t* s, int rad)
    {
      auto t = i;
      auto r = s;
      wchar_t symbols[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

      if (i < 0)
      {
        i = -i;
        *s++ = '-';
      }
      do
      {
        ++s;
      } while (t /= rad);
      *s = '\0';
      do
      {
        *--s = symbols[i % rad];
      } while (i /= rad);
      return r;
    }

    const char* UnsignedIntToArray(unsigned i, char* s, unsigned rad)
    {
      auto t = i;
      auto r = s;
      char symbols[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

      do
      {
        ++s;
      } while (t /= rad);
      *s = '\0';
      do
      {
        *--s = symbols[i % rad];
      } while (i /= rad);
      return r;
    }

    const wchar_t* UnsignedIntToArray(unsigned i, wchar_t* s, unsigned rad)
    {
      auto t = i;
      auto r = s;
      wchar_t symbols[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

      do
      {
        ++s;
      } while (t /= rad);
      *s = '\0';
      do
      {
        *--s = symbols[i % rad];
      } while (i /= rad);
      return r;
    }

  }
}

#pragma optimize("", on)
