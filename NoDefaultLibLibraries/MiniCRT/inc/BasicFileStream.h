#pragma once
#include "BasicString.h"
#include "BasicFileStreamImpl.h"

namespace MiniCRT
{
  template<class charT>
  class BasicFileStream
  {
  public:
    using ModeAccess = int;

    static const ModeAccess in    = 1 << 0; // File open for reading
    static const ModeAccess out   = 1 << 1; // File open for writing, create if it doesn't exist
    static const ModeAccess ate   = 1 << 2; // The output position starts at the end of the file
    static const ModeAccess app   = 1 << 3; // All output operations happen at the end of the file, appending to its existing contents
    static const ModeAccess trunc = 1 << 4; // Any contents that existed in the file before it is open are discarded

    enum class SeekDirection : int
    {
      Beg = 0, // The starting point is zero or the beginning of the file.
      Cur = 1, // The starting point is the current position of the file pointer.
      End = 2  // The starting point is the end of the file.
    };

    /// <summary>
    /// Default constructor that initializes the file stream to a null/zero state
    /// </summary>
    BasicFileStream()
      : m_file(nullptr)
      , m_mode(0)
      , m_lastError()
    {}

    /// <summary>
    /// Create a file stream and open the specified file with the given access mode.
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="mode"></param>
    BasicFileStream(const BasicString<charT>& filename, const ModeAccess mode = in | out)
      : m_file(nullptr)
      , m_mode(0)
      , m_lastError()
    {
      Open(filename, mode);
    }

    BasicFileStream(const BasicFileStream&) = delete;

    /// <summary>
    /// Move constructor that transfers ownership of the underlying file handle 
    /// and mode from another BasicFileStream, leaving the source in a 
    /// null/zero state. The operation is noexcept.
    /// </summary>
    /// <param name="other"></param>
    BasicFileStream(BasicFileStream&& other) noexcept
      : m_file(other.m_file)
      , m_mode(other.m_mode)
      , m_lastError()
    {
      other.m_file = nullptr;
      other.m_mode = 0;
    }

    /// <summary>
    /// Move-assigns from another BasicFileStream by constructing a temporary from the source and swapping its state into this object. The operation is noexcept.
    /// </summary>
    /// <param name="other"></param>
    /// <returns></returns>
    BasicFileStream& operator=(BasicFileStream&& other) noexcept
    {
      BasicFileStream(MiniCRT::Move(other)).Swap(*this);
      return *this;
    }

   ~BasicFileStream()
    {
      Close();
    }

    void Swap(BasicFileStream& other)
    {
      MiniCRT::Swap(m_file, other.m_file);
      MiniCRT::Swap(m_mode, other.m_mode);
      MiniCRT::Swap(m_lastError, other.m_lastError);
    }

    /// <summary>
    /// Open a file with the specified name and access mode. 
    /// The function returns true if the file was opened 
    /// successfully, and false otherwise.
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="mode"></param>
    /// <returns></returns>
    bool Open(const BasicString<charT>& filename, const ModeAccess mode = in | out)
    {
      return Open(filename.c_str(), mode);
    }

    /// <summary>
    /// Open a file with the specified name and access mode.
    /// The function returns true if the file was opened 
    /// successfully, and false otherwise.
    /// </summary>
    /// <param name="filename"></param>
    /// <param name="mode"></param>
    /// <returns></returns>
    bool Open(const charT* filename, const ModeAccess mode = in | out)
    {
      if ((mode & trunc) && (mode & app) || (mode & trunc) && !(mode & out))
        return false; // Can't truncate and append at the same time or truncate and open as read only at the same time

      if (m_file = Impl::Open(filename, mode, &m_lastError); m_file != nullptr)
      {
        if (mode & ate)
          Impl::SeekToEnd(m_file);
        m_mode = mode;
        return true;
      }

      m_lastError = GetLastError();
      return false;
    }

    /// <summary>
    /// Close the file if it is open. After this function is called, 
    /// the file handle is no longer valid and should not be used.
    /// </summary>
    void Close()
    {
      Impl::Close(m_file);
      m_file = nullptr;
      m_mode = 0;
    }

    /// <summary>
    /// Read data from the file into the provided buffer. The function 
    /// returns the number of characters read, which may be less than 
    /// count if the end of the file is reached or if an error occurs.
    /// </summary>
    /// <param name="buffer"></param>
    /// <param name="count"></param>
    /// <returns></returns>
    size_t Read(charT* buffer, size_t count)
    {
      unsigned long bytesRead = 0;
      if (m_file)
      {
        Impl::ReadFile(m_file, buffer, static_cast<unsigned long>(sizeof(charT) * count), &bytesRead, &m_lastError);
      }
      return bytesRead;
    }

    /// <summary>
    /// Write data from the provided buffer to the file. The function 
    /// returns the number of characters written, which may be less than 
    /// count if an error occurs.
    /// </summary>
    /// <param name="buffer"></param>
    /// <param name="count"></param>
    /// <returns></returns>
    size_t Write(const charT* buffer, size_t count)
    {
      unsigned long bytesWritten = 0;
      if (m_file)
      {
        if (m_mode & app)
          Impl::SeekToEnd(m_file);

        Impl::WriteFile(m_file, buffer, static_cast<unsigned long>(sizeof(charT) * count), &bytesWritten, &m_lastError);
      }
      return bytesWritten;
    }

    /// <summary>
    /// Returns the current position of the file pointer, which is 
    /// the offset in bytes from the beginning of the file. This 
    /// can be used to determine how much data has been read or 
    /// written, or to save the current position for later use.
    /// </summary>
    /// <param name="file"></param>
    /// <returns></returns>
    size_t Tell() const
    {
      return Impl::Tell(m_file);
    }

    /// <summary>
    /// Sets the position of the file pointer to pos.
    /// 
    /// </summary>
    /// <param name="file"></param>
    /// <param name="pos"></param>
    /// <param name="way"></param>
    BasicFileStream& Seek(size_t pos)
    {
      return Seek(pos, SeekDirection::Beg);
    }

    /// <summary>
    /// Sets the position of the file pointer to pos. The way parameter specifies how the pos value is interpreted, and can be one of the following:
    /// 
    /// </summary>
    /// <param name="file"></param>
    /// <param name="pos"></param>
    /// <param name="way"></param>
    BasicFileStream& Seek(size_t off, SeekDirection way)
    {
      Impl::Seek(m_file, off, static_cast<int>(way));
      return *this;
    }

    /// <summary>
    /// Returns the size of the file in bytes.
    /// </summary>
    /// <returns></returns>
    size_t Size()
    {
      auto currentPos = Tell();
      auto size = Seek(0, SeekDirection::End).Tell();
      Seek(currentPos, SeekDirection::Beg);
      return size;
    }

    /// <summary>
    /// Returns the last error code that occurred during file operations.
    /// </summary>
    /// <returns></returns>
    unsigned long GetLastError() const
    {
      return m_lastError;
    }

    /// <summary>
    /// Returns true if the file stream is currently open and valid, 
    /// and false otherwise.
    /// </summary>
    operator bool() const
    {
      return m_file != nullptr;
    }

  private:
    void* m_file;
    ModeAccess m_mode;
    unsigned long m_lastError;
  };
}
