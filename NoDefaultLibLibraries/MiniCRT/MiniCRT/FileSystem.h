#pragma once
#include "BasicString.h"
#include "BasicFilesystemImpl.h"

namespace MiniCRT
{
  /// <summary>
  /// Remove a file with the specified name. The function returns 
  /// true if successfully removed the file, and false otherwise.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="filename"></param>
  /// <returns></returns>
  template<class charT>
  inline bool RemoveFile(const charT* filename)
  {
    return Impl::RemoveFile(filename);
  }

  /// <summary>
  /// Remove a file with the specified name. The function returns 
  /// true if successfully removed the file, and false otherwise.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="filename"></param>
  /// <returns></returns>
  template<class charT>
  inline bool RemoveFile(const BasicString<charT>& filename)
  {
    return Impl::RemoveFile(filename.c_str());
  }

  /// <summary>
  /// Move or rename a file from oldname to newname. The function 
  /// returns true if the file was moved successfully, and false 
  /// if otherwise
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="oldname"></param>
  /// <param name="newname"></param>
  /// <returns></returns>
  template<class charT>
  inline bool MoveFile(const charT* oldname, const charT* newname)
  {
    return Impl::MoveFile(oldname, newname);
  }

  /// <summary>
  /// Move or rename a file from oldname to newname. The function 
  /// returns true if the file was moved successfully, and false 
  /// if otherwise
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="oldname"></param>
  /// <param name="newname"></param>
  /// <returns></returns>
  template<class charT>
  inline bool MoveFile(const BasicString<charT>& oldname, const BasicString<charT>& newname)
  {
    return Impl::MoveFile(oldname.c_str(), newname.c_str());
  }

  /// <summary>
  /// Create a new folder with the specified name. The function 
  /// returns true if the folder was created successfully, and 
  /// false otherwise.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="filename"></param>
  /// <returns></returns>
  template<class charT>
  inline bool CreateFolder(const charT* filename)
  {
    return Impl::CreateFolder(filename);
  }

  /// <summary>
  /// Create a new folder with the specified name. The function 
  /// returns true if the folder was created successfully, and 
  /// false otherwise.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="filename"></param>
  /// <returns></returns>
  template<class charT>
  inline bool CreateFolder(const BasicString<charT>& filename)
  {
    return Impl::CreateFolder(filename.c_str());
  }

  /// <summary>
  /// Remove the specified folder. The folder must be empty for this 
  /// function to succeed.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="filename"></param>
  /// <returns></returns>
  template<class charT>
  inline bool RemoveFolder(const charT* filename)
  {
    return Impl::RemoveFolder(filename);
  }

  /// <summary>
  /// Remove the specified folder. The folder must be empty for this 
  /// function to succeed.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="filename"></param>
  /// <returns></returns>
  template<class charT>
  inline bool RemoveFolder(const BasicString<charT>& filename)
  {
    return Impl::RemoveFolder(filename.c_str());
  }

  /// <summary>
  /// Returns the current working directory as a BasicString.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <returns></returns>
  template<class charT>
  inline BasicString<charT> CurrentDirectory()
  {
    constexpr auto maxPath = 1024;
    charT buf[maxPath]{};
    const auto size = Impl::CurrentDirectory(buf, sizeof(buf) / sizeof(charT));
    return BasicString<charT>(buf, size);
  }

  /// <summary>
  /// Change the current working directory to the specified path. The function 
  /// returns true if the current directory was changed successfully, or false otherwise.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="path"></param>
  /// <returns></returns>
  template<class charT>
  inline bool CurrentDirectory(const charT* path)
  {
    return Impl::CurrentDirectory(path);
  }

  /// <summary>
  /// Change the current working directory to the specified path. The function 
  /// returns true if the current directory was changed successfully, or false otherwise.
  /// </summary>
  /// <typeparam name="charT"></typeparam>
  /// <param name="path"></param>
  /// <returns></returns>
  template<class charT>
  inline bool CurrentDirectory(const BasicString<charT>& path)
  {
    return Impl::CurrentDirectory(path.c_str());
  }
}
