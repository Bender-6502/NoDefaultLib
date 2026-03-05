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

    BasicFileStream()
      : m_file(nullptr)
      , m_mode(0)
      , m_lastError()
    {}

    BasicFileStream(const BasicString<charT>& filename, const ModeAccess mode = in | out)
      : m_file(nullptr)
      , m_mode(0)
      , m_lastError()
    {
      Open(filename, mode);
    }

    BasicFileStream(const BasicFileStream&) = delete;

    BasicFileStream(BasicFileStream&& other)
      : m_file(other.m_file)
      , m_mode(other.m_mode)
      , m_lastError()
    {
      other.m_file = nullptr;
      other.m_mode = 0;
    }

    BasicFileStream& operator=(BasicFileStream&& other)
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

    bool Open(const BasicString<charT>& filename, const ModeAccess mode = in | out)
    {
      return Open(filename.c_str(), mode);
    }

    bool Open(const charT* filename, const ModeAccess mode = in | out)
    {
      if ((mode & trunc) && (mode & app) || (mode & trunc) && !(mode & out))
        return false; // Can't truncate and append at the same time or truncate and open as read only at the same time

      if (m_file = Impl::Open(filename, mode, &m_lastError); m_file != nullptr)
      {
        if (mode & ate)
          Impl::MoveToEnd(m_file);
        m_mode = mode;
        return true;
      }

      m_lastError = GetLastError();
      return false;
    }

    void Close()
    {
      Impl::Close(m_file);
      m_file = nullptr;
      m_mode = 0;
    }

    size_t Read(charT* buffer, size_t count)
    {
      unsigned long bytesRead = 0;
      if (m_file)
      {
        Impl::ReadFile(m_file, buffer, static_cast<unsigned long>(sizeof(charT) * count), &bytesRead, &m_lastError);
      }
      return bytesRead;
    }

    size_t Write(const charT* buffer, size_t count)
    {
      unsigned long bytesWritten = 0;
      if (m_file)
      {
        if (m_mode & app)
          Impl::MoveToEnd(m_file);

        Impl::WriteFile(m_file, buffer, static_cast<unsigned long>(sizeof(charT) * count), &bytesWritten, &m_lastError);
      }
      return bytesWritten;
    }

    unsigned long GetLastError() const
    {
      return m_lastError;
    }

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
