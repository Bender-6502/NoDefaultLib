#include "BasicFileSystemImpl.h"

#include <Windows.h>


namespace MiniCRT
{
  namespace Impl
  {
    bool RemoveFile(const char* filename)
    {
      return DeleteFileA(filename) != 0;
    }

    bool RemoveFile(const wchar_t* filename)
    {
      return DeleteFileW(filename) != 0;
    }

    bool MoveFile(const char* oldname, const char* newname)
    {
      return MoveFileA(oldname, newname) != 0;
    }

    bool MoveFile(const wchar_t* oldname, const wchar_t* newname)
    {
      return MoveFileW(oldname, newname) != 0;
    }

    bool CreateFolder(const char* filename)
    {
      return CreateDirectoryA(filename, nullptr) != 0;
    }

    bool CreateFolder(const wchar_t* filename)
    {
      return CreateDirectoryW(filename, nullptr) != 0;
    }

    bool RemoveFolder(const char* filename)
    {
      return RemoveDirectoryA(filename) != 0;
    }

    bool RemoveFolder(const wchar_t* filename)
    {
      return RemoveDirectoryW(filename) != 0;
    }

    size_t CurrentDirectory(char* buffer, size_t size)
    {
      return GetCurrentDirectoryA(static_cast<DWORD>(size), buffer);
    }

    size_t CurrentDirectory(wchar_t* buffer, size_t size)
    {
      return GetCurrentDirectoryW(static_cast<DWORD>(size), buffer);
    }

    bool CurrentDirectory(const char* path)
    {
      return SetCurrentDirectoryA(path) != 0;
    }

    bool CurrentDirectory(const wchar_t* path)
    {
      return SetCurrentDirectoryW(path) != 0;
    }
  }
}
