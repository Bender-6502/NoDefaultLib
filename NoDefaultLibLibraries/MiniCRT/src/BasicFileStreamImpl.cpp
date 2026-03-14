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

      unsigned long GetSeekMethod(const int seek)
      {
        if (seek == static_cast<int>(BasicFileStream<char>::SeekDirection::End))
          return FILE_END;
        if (seek == static_cast<int>(BasicFileStream<char>::SeekDirection::Cur))
          return FILE_CURRENT;
        return FILE_BEGIN;
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

    unsigned long Tell(void* file)
    {
      if (file == nullptr)
        return -1;
      auto pos = ::SetFilePointer(file, 0, nullptr, FILE_CURRENT);
      if (pos == INVALID_SET_FILE_POINTER)
        return -1;
      return pos;
    }

    void Seek(void* file, size_t pos, int way)
    {
      if (file != nullptr)
        ::SetFilePointer(file, static_cast<LONG>(pos), nullptr, GetSeekMethod(way));
    }

    void SeekToEnd(void* file)
    {
      if (file != nullptr)
        ::SetFilePointer(file, 0, nullptr, FILE_END);
    }

    bool Eof(void* file)
    {
      auto pos = Tell(file);
      SeekToEnd(file);
      auto eof = pos == Tell(file);
      Seek(file, pos, 0);
      return eof;
    }
  }
}
