#pragma once

namespace MiniCRT
{
  namespace Impl
  {
    /// <summary>
    /// Remove a file with the specified name. The function returns 
    /// true if the file  
    /// </summary>
    /// <param name="oldname"></param>
    /// <param name="newname"></param>
    /// <returns></returns>
    bool RemoveFile(const char* filename);

    /// <summary>
    /// Remove a file with the specified name. The function returns 
    /// true if the file  
    /// </summary>
    /// <param name="oldname"></param>
    /// <param name="newname"></param>
    /// <returns></returns>
    bool RemoveFile(const wchar_t* filename);

    /// <summary>
    /// Move or rename a file from oldname to newname. The function 
    /// returns true if the file was moved successfully, and false 
    /// otherwise.
    /// </summary>
    /// <param name="filename"></param>
    /// <returns></returns>
    bool MoveFile(const char* oldname, const char* newname);

    /// <summary>
    /// Move or rename a file from oldname to newname. The function 
    /// returns true if the file was moved successfully, and false 
    /// otherwise.
    /// </summary>
    /// <param name="filename"></param>
    /// <returns></returns>
    bool MoveFile(const wchar_t* oldname, const wchar_t* newname);

    /// <summary>
    /// Create a new folder with the specified name. The function 
    /// returns true if the folder was created successfully, and 
    /// false otherwise.
    /// </summary>
    bool CreateFolder(const char* filename);

    /// <summary>
    /// Create a new folder with the specified name. The function 
    /// returns true if the folder was created successfully, and 
    /// false otherwise.
    /// </summary>
    bool CreateFolder(const wchar_t* filename);

    /// <summary>
    /// Remove the specified folder. The folder must be empty for this 
    /// function to succeed.
    /// </summary>
    bool RemoveFolder(const char* filename);

    /// <summary>
    /// Remove the specified folder. The folder must be empty for this 
    /// function to succeed.
    /// </summary>
    bool RemoveFolder(const wchar_t* filename);

    /// <summary>
    /// Get the current directory and write it to the provided buffer. 
    /// The size parameter is the size of the buffer in characters, 
    /// including the null terminator. The function returns the number 
    /// of characters written to the buffer, excluding the null terminator. 
    /// If the buffer is too small to hold the current directory, the 
    /// function returns 0 and does not modify the buffer.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    size_t CurrentDirectory(char* buffer, size_t size);

    /// <summary>
    /// Get the current directory and write it to the provided buffer. 
    /// The size parameter is the size of the buffer in characters, 
    /// including the null terminator. The function returns the number 
    /// of characters written to the buffer, excluding the null terminator. 
    /// If the buffer is too small to hold the current directory, the 
    /// function returns 0 and does not modify the buffer.
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    size_t CurrentDirectory(wchar_t* buffer, size_t size);

    /// <summary>
    /// Set current directory to the specified path. 
    /// The path must exist and be a directory, 
    /// otherwise this function will fail and return false.
    /// </summary>
    bool CurrentDirectory(const char* path);

    /// <summary>
    /// Set current directory to the specified path. 
    /// The path must exist and be a directory, 
    /// otherwise this function will fail and return false.
    /// </summary>
    bool CurrentDirectory(const wchar_t* path);
  }
}
