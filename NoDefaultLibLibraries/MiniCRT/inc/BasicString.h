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

    /// <summary>
    /// Default constructor that initializes the BasicString to an empty string.
    /// </summary>
    BasicString()
      : m_length()
      , m_str(Alloc::Allocate(1))
    {
      m_str[0] = '\0';
    }

    /// <summary>
    /// Construct a BasicString from a pointer to a null-terminated character array.
    /// </summary>
    /// <param name="str"></param>
    BasicString(const charT* str)
      : m_length()
      , m_str(Alloc::Allocate(1))
    {
      m_str[0] = '\0';
      Assign(str);
    }

    /// <summary>
    /// Construct a BasicString from a pointer to a character array and its length. 
    /// The character array does not need to be null-terminated, as the length 
    /// parameter specifies the number of characters to copy. The resulting 
    /// BasicString will be null-terminated.
    /// </summary>
    /// <param name="str"></param>
    /// <param name="length"></param>
    BasicString(const charT* str, size_t length)
      : m_length()
      , m_str(nullptr)
    {
      Assign(str, length);
    }

    /// <summary>
    /// Copy constructor that creates a new BasicString as a copy of an 
    /// existing BasicString.
    /// </summary>
    /// <param name="str"></param>
    BasicString(const BasicString<charT>& str) noexcept
      : m_length()
      , m_str(nullptr)
    {
      Assign(str);
    }

    /// <summary>
    /// Move constructor that takes ownership of the source object's resources 
    /// and leaves the source in a valid, empty state. The operation is noexcept.
    /// </summary>
    /// <param name="str"></param>
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

    /// <summary>
    /// Assign the specified string to this string, replacing the current contents.
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    BasicString& operator=(const charT* str) noexcept
    {
      BasicString(str).Swap(*this);
      return *this;
    }

    /// <summary>
    /// Assign the specified string to this string, replacing the current contents.
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    BasicString& operator=(const BasicString& str) noexcept
    {
      BasicString(str).Swap(*this);
      return *this;
    }

    /// <summary>
    /// Assign the specified string to this string, replacing the current contents.
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
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

    /// <summary>
    /// Assign the specified string to this string, replacing the current contents.
    /// </summary>
    /// <param name="str"></param>
    /// <param name="length"></param>
    void Assign(const charT* str)
    {
      if (str)
        Assign(str, StringLength(str));
    }

    /// <summary>
    /// Assign the specified string to this string, replacing the current contents.
    /// </summary>
    /// <param name="str"></param>
    /// <param name="length"></param>
    void Assign(const BasicString<charT>& str)
    {
      Assign(str.m_str, str.m_length);
    }

    /// <summary>
    /// Assign the specified string to this string, replacing the current contents.
    /// </summary>
    /// <param name="str"></param>
    /// <param name="length"></param>
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

    /// <summary>
    /// Append the specified string to the end of this string.
    /// </summary>
    /// <param name="str"></param>
    /// <param name="length"></param>
    void Append(const charT* str)
    {
      if (str)
        Append(str, StringLength(str));
    }

    /// <summary>
    /// Append the specified string to the end of this string.
    /// </summary>
    /// <param name="str"></param>
    /// <param name="length"></param>
    void Append(const BasicString& str)
    {
      Append(str.m_str, str.m_length);
    }

    /// <summary>
    /// Append the specified string to the end of this string.
    /// </summary>
    /// <param name="str"></param>
    /// <param name="length"></param>
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

    /// <summary>
    /// Returns a substring of this string starting at the specified position and
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    BasicString SubStr(size_t pos) const
    {
      return SubStr(pos, m_length - pos);
    }

    /// <summary>
    /// Returns a substring of this string starting at the specified position and 
    /// with the specified length. If the starting position is greater than the 
    /// length of the string, an empty string is returned. If the starting position 
    /// plus the length exceeds the length of the string, the substring from the 
    /// starting position to the end of the string is returned.
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="count"></param>
    /// <returns></returns>
    BasicString SubStr(size_t pos, size_t count) const
    {
      if (pos > m_length)
        return BasicString();
      if (pos + count > m_length)
        count = m_length - pos;
      return BasicString(&m_str[pos], count);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    charT& operator[] (size_t pos)
    {
      return m_str[pos];
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="pos"></param>
    /// <returns></returns>
    const charT& operator[] (size_t pos) const
    {
      return m_str[pos];
    }

    /// <summary>
    /// Compare this string with a pointer to a char array. The function 
    /// returns true if the two strings are equal, and false otherwise.
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    bool Compare(const charT* str) const
    {
      return StringCompare(m_str, m_length, str, StringLength(str));
    }

    /// <summary>
    /// Compare this string with another BasicString. The function 
    /// returns true if the two strings are equal, and false otherwise.
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    bool Compare(const BasicString& str) const
    {
      return StringCompare(m_str, m_length, str.m_str, str.m_length);
    }

    /// <summary>
    /// Return a pointer to the underlying character array, 
    /// which is null-terminated.
    /// </summary>
    /// <returns></returns>
    const charT* c_str() const
    {
      return m_str;
    }

    /// <summary>
    /// Return the length of the string, which is the number of 
    /// characters in the string, excluding the null terminator.
    /// </summary>
    /// <returns></returns>
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
  inline BasicString<charT, Alloc> operator+(const BasicString<charT, Alloc>& lhs, const charT* rhs)
  {
    BasicString<charT, Alloc> result(lhs);
    result.Append(rhs);
    return result;
  }

  template <class charT, class Alloc = BasicStringAllocator<charT>>
  inline BasicString<charT, Alloc> operator+(const charT* lhs, const BasicString<charT, Alloc>& rhs)
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
