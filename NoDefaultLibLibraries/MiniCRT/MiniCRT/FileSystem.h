#pragma once
#include "BasicString.h"
#include "BasicFilesystemImpl.h"

namespace MiniCRT
{
  template<class charT>
  inline bool RemoveFile(const charT* filename)
  {
    return Impl::RemoveFile(filename);
  }

  template<class charT>
  inline bool RemoveFile(const BasicString<charT>& filename)
  {
    return Impl::RemoveFile(filename.c_str());
  }

  template<class charT>
  inline bool MoveFile(const charT* oldname, const charT* newname)
  {
    return Impl::MoveFile(oldname, newname);
  }

  template<class charT>
  inline bool MoveFile(const BasicString<charT>& oldname, const BasicString<charT>& newname)
  {
    return Impl::MoveFile(oldname.c_str(), newname.c_str());
  }

  template<class charT>
  inline bool CreateFolder(const charT* filename)
  {
    return Impl::CreateFolder(filename);
  }

  template<class charT>
  inline bool CreateFolder(const BasicString<charT>& filename)
  {
    return Impl::CreateFolder(filename.c_str());
  }

  template<class charT>
  inline bool RemoveFolder(const charT* filename)
  {
    return Impl::RemoveFolder(filename);
  }

  template<class charT>
  inline bool RemoveFolder(const BasicString<charT>& filename)
  {
    return Impl::RemoveFolder(filename.c_str());
  }

  template<class charT>
  inline BasicString<charT> CurrentDirectory()
  {
    constexpr auto maxPath = 1024;
    charT buf[maxPath]{};
    const auto size = Impl::CurrentDirectory(buf, sizeof(buf) / sizeof(charT));
    return BasicString<charT>(buf, size);
  }

  template<class charT>
  inline bool CurrentDirectory(const charT* path)
  {
    return Impl::CurrentDirectory(path);
  }

  template<class charT>
  inline bool CurrentDirectory(const BasicString<charT>& path)
  {
    return Impl::CurrentDirectory(path.c_str());
  }
}
