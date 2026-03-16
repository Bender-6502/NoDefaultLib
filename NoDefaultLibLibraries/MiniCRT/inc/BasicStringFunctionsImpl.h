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

    /// <summary>
    /// Convert int to string array
    /// </summary>
    /// <param name="i"></param>
    /// <param name="s"></param>
    /// <param name="rad"></param>
    /// <returns></returns>
    const char* IntToArray(int i, char* s, int rad);
    const wchar_t* IntToArray(int i, wchar_t* s, int rad);

    /// <summary>
    /// Convert unsigned int to string array
    /// </summary>
    /// <param name="i"></param>
    /// <param name="s"></param>
    /// <param name="rad"></param>
    /// <returns></returns>
    const char* UnsignedIntToArray(unsigned i, char* s, unsigned rad);
    const wchar_t* UnsignedIntToArray(unsigned i, wchar_t* s, unsigned rad);
  }
}
