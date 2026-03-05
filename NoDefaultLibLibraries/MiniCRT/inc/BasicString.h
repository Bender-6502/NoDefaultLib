#pragma once

#include "BasicStringAllocator.h"
#include "BasicStringFunctions.h"
#include "../MiniCRT/Traits.h"

namespace MiniCRT
{
  template <class charT, class Alloc = BasicStringAllocator<charT>>
  class BasicString
  {
  public:

    BasicString()
      : m_length()
      , m_str(Alloc::Allocate(1))
    {
      m_str[0] = '\0';
    }

    BasicString(const charT* str)
      : m_length()
      , m_str(Alloc::Allocate(1))
    {
      m_str[0] = '\0';
      Assign(str);
    }

    BasicString(const charT* str, size_t length)
      : m_length()
      , m_str(nullptr)
    {
      Assign(str, length);
    }

    BasicString(const BasicString<charT>& str) noexcept
      : m_length()
      , m_str(nullptr)
    {
      Assign(str);
    }

    BasicString(BasicString&& str) noexcept
      : m_length(str.m_length)
      , m_str(str.m_str)
    {
      str.m_length = 0;
      str.m_str = nullptr;
    }

    ~BasicString()
    {
      Alloc::Deallocate(m_str);
    }

    BasicString& operator=(const charT* str) noexcept
    {
      BasicString(str).Swap(*this);
      return *this;
    }

    BasicString& operator=(const BasicString& str) noexcept
    {
      BasicString(str).Swap(*this);
      return *this;
    }

    BasicString& operator=(BasicString&& str) noexcept
    {
      BasicString(MiniCRT::Move(str)).Swap(*this);
      return *this;
    }

    void Swap(BasicString& other)
    {
      MiniCRT::Swap(m_length, other.m_length);
      MiniCRT::Swap(m_str, other.m_str);
    }

    void Assign(const charT* str)
    {
      if (str)
        Assign(str, StringLength(str));
    }

    void Assign(const BasicString<charT>& str)
    {
      Assign(str.m_str, str.m_length);
    }

    void Assign(const charT* str, size_t length)
    {
      if (str)
      {
        if (auto new_str = Alloc::Allocate(length + 1); new_str != nullptr)
        {
          StringCopy(new_str, length, str, length);
          Alloc::Deallocate(m_str);
          m_length = length;
          m_str = new_str;
        }
      }
    }

    void Append(const charT* str)
    {
      if (str)
        Append(str, StringLength(str));
    }

    void Append(const BasicString& str)
    {
      Append(str.m_str, str.m_length);
    }

    void Append(const charT* str, size_t length)
    {
      if (str)
      {
        auto new_length = m_length + length;
        if (auto new_str = Alloc::Allocate(new_length + 1); new_str != nullptr)
        {
          StringCopy(&new_str[0], new_length, m_str, m_length);
          StringCopy(&new_str[m_length], new_length - m_length, str, length);
          Alloc::Deallocate(m_str);
          m_length = new_length;
          m_str = new_str;
        }
      }
    }

    bool Compare(const charT* str) const
    {
      return StringCompare(m_str, m_length, str, StringLength(str));
    }

    bool Compare(const BasicString& str) const
    {
      return StringCompare(m_str, m_length, str.m_str, str.m_length);
    }

    const charT* c_str() const
    {
      return m_str;
    }

    size_t Length() const
    {
      return m_length;
    }

  private:
    size_t m_length;
    charT* m_str;
  };

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline bool operator==(const BasicString<charT, Alloc>& lhs, const BasicString<charT, Alloc>& rhs)
  {
    return lhs.Compare(rhs);
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline bool operator==(const charT* lhs, const BasicString<charT, Alloc>& rhs)
  {
    return rhs.Compare(lhs);
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline bool operator==(const BasicString<charT, Alloc>& lhs, const charT* rhs)
  {
    return lhs.Compare(rhs);
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline bool operator!=(const BasicString<charT, Alloc>& lhs, const BasicString<charT, Alloc>& rhs)
  {
    return !(lhs == rhs);
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline bool operator!=(const charT* lhs, const BasicString<charT, Alloc>& rhs)
  {
    return !(lhs == rhs);
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline bool operator!=(const BasicString<charT, Alloc>& lhs, const charT* rhs)
  {
    return !(lhs == rhs);
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline BasicString<charT, Alloc> operator+(const BasicString<charT, Alloc>& lhs, const BasicString<charT, Alloc>& rhs)
  {
    BasicString<charT, Alloc> result(lhs);
    result.Append(rhs);
    return result;
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline BasicString<charT, Alloc>& operator+=(BasicString<charT, Alloc>& lhs, const BasicString<charT, Alloc>& rhs)
  {
    lhs.Append(rhs);
    return lhs;
  }

}
