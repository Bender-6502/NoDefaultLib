#pragma once

namespace MiniCRT
{
  namespace Impl
  {
    /// <summary>
    /// Open a file with the specified name and access mode. 
    /// The function returns a file handle if the file was 
    /// opened successfully, and nullptr otherwise.
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="accessMode"></param>
    /// <param name="lastError"></param>
    /// <returns></returns>
    void* Open(const char* filename, const unsigned long accessMode, unsigned long* lastError);

    /// <summary>
    /// Open a file with the specified name and access mode. 
    /// The function returns a file handle if the file was 
    /// opened successfully, and nullptr otherwise.
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="accessMode"></param>
    /// <param name="lastError"></param>
    /// <returns></returns>
    void* Open(const wchar_t* filename, const unsigned long accessMode, unsigned long* lastError);

    /// <summary>
    /// Close the specified file handle. After this function 
    /// is called, the file handle is no longer valid and 
    /// should not be used.
    /// </summary>
    void Close(void* file);

    /// <summary>
    /// Move the file pointer to the end of the file. This is 
    /// typically used for appending to a file, where you want 
    /// to write new data at the end of the existing contents.
    /// </summary>
    void SeekToEnd(void* file);

    /// <summary>
    /// Read data from the specified file into the provided buffer.
    /// </summary>
    bool ReadFile(void* file, void* lpBuffer, const unsigned long nNumberOfBytesToRead, unsigned long* lpNumberOfBytesRead, unsigned long* lastError);

    /// <summary>
    /// Write data from the provided buffer to the specified file.
    /// </summary>
    bool WriteFile(void* file, const void* lpBuffer, const unsigned long nNumberOfBytesToWrite, unsigned long* lpNumberOfBytesWritten, unsigned long* lastError);

    /// <summary>
    /// Returns the current position of the file pointer, which is 
    /// the offset in bytes from the beginning of the file. This 
    /// can be used to determine how much data has been read or 
    /// written, or to save the current position for later use.
    /// </summary>
    /// <param name="file"></param>
    /// <returns></returns>
    unsigned long Tell(void* file);

    /// <summary>
    /// Sets the position of the file pointer to pos. The way parameter specifies how the pos value is interpreted, and can be one of the following:
    /// 
    /// </summary>
    /// <param name="file"></param>
    /// <param name="pos"></param>
    /// <param name="way"></param>
    void Seek(void* file, size_t pos, int way);

    /// <summary>
    /// Returns true if end of file reached
    /// </summary>
    /// <param name="lastError"></param>
    /// <returns></returns>
    bool Eof(void* file);
  };
}
