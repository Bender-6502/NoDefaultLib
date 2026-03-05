#include "BasicFileStreamImpl.h"
#include "BasicFileStream.h"

#include <Windows.h>

namespace MiniCRT
{
  namespace Impl
  {

    namespace
    {
      unsigned long GetAccessMode(const BasicFileStream<char>::ModeAccess mode)
      {
        unsigned long access = 0;
        if (mode & BasicFileStream<char>::in)
          access |= GENERIC_READ;
        if (mode & BasicFileStream<char>::out)
          access |= GENERIC_WRITE;
        return access;
      }

      unsigned long GetCreationDisposition(const BasicFileStream<char>::ModeAccess mode)
      {
        if (mode == BasicFileStream<char>::in)                                 /* Read only */
          return OPEN_EXISTING;
        if (mode == BasicFileStream<char>::out + BasicFileStream<char>::app)
          return OPEN_ALWAYS;
        if (mode == BasicFileStream<char>::out)                                /* Write only */
          return CREATE_NEW;
        if (mode == BasicFileStream<char>::in + BasicFileStream<char>::out)    /* Read and write */
          return OPEN_ALWAYS;
        if (mode == BasicFileStream<char>::out + BasicFileStream<char>::trunc) /* Replace and write */
          return CREATE_ALWAYS;
        return 0;
      }
    }

    void* Open(const char* filename, const unsigned long accessMode, unsigned long* lastError)
    {
      if (auto handle = ::CreateFileA(filename, GetAccessMode(accessMode), 0, nullptr, GetCreationDisposition(accessMode), FILE_ATTRIBUTE_NORMAL, nullptr); handle != INVALID_HANDLE_VALUE)
        return handle;

      if (lastError)
        *lastError = GetLastError();

      return nullptr;
    }

    void* Open(const wchar_t* filename, const unsigned long accessMode, unsigned long* lastError)
    {
      if (auto handle = ::CreateFileW(filename, GetAccessMode(accessMode), 0, nullptr, GetCreationDisposition(accessMode), FILE_ATTRIBUTE_NORMAL, nullptr); handle != INVALID_HANDLE_VALUE)
        return handle;

      if (lastError)
        *lastError = GetLastError();

      return nullptr;
    }

    void Close(void* handle)
    {
      if (handle != nullptr)
        ::CloseHandle(handle);
    }

    void MoveToEnd(void* file)
    {
      if (file != nullptr)
        ::SetFilePointer(file, 0, nullptr, FILE_END);
    }

    bool ReadFile(void* file, void* lpBuffer, const unsigned long nNumberOfBytesToRead, unsigned long* lpNumberOfBytesRead, unsigned long* lastError)
    {
      if (!::ReadFile(file, lpBuffer, static_cast<DWORD>(nNumberOfBytesToRead), lpNumberOfBytesRead, nullptr))
      {
        if (lastError)
          *lastError = GetLastError();

        if (lpNumberOfBytesRead)
          *lpNumberOfBytesRead = 0;

        return false;
      }
      return true;
    }

    bool WriteFile(void* file, const void* lpBuffer, const unsigned long nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, unsigned long* lastError)
    {
      if (!::WriteFile(file, lpBuffer, static_cast<DWORD>(nNumberOfBytesToWrite), lpNumberOfBytesWritten, nullptr))
      {
        if (lastError)
          *lastError = GetLastError();

        if (lpNumberOfBytesWritten)
          *lpNumberOfBytesWritten = 0;

        return false;
      }
      return true;
    }
  }
}
