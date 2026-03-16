#pragma once
#include "../MiniCRT/Traits.h"
#include "BasicNew.h"

namespace MiniCRT
{
  template<class T>
  class UniquePtr
  {
  public:
    UniquePtr()
      : m_ptr()
    {}

    explicit UniquePtr(T* ptr)
      : m_ptr(ptr)
    {}

    UniquePtr(UniquePtr&& other) noexcept
      : m_ptr(other.m_ptr)
    {
      other.m_ptr = nullptr;
    }

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
      UniquePtr<T>(MiniCRT::Move(other)).Swap(*this);
      return *this;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

    ~UniquePtr()
    {
      Reset();
    }

    void Swap(UniquePtr& other) noexcept
    {
      MiniCRT::Swap(m_ptr, other.m_ptr);
    }

    void Reset(T* ptr = nullptr) noexcept
    {
      delete m_ptr;
      m_ptr = ptr;
    }

    T* Get() const noexcept
    {
      return m_ptr;
    }

    explicit operator bool() const noexcept
    {
      return m_ptr != nullptr;
    }

    T& operator*() const noexcept
    {
      return *m_ptr;
    }

    T* operator->() const noexcept
    {
      return m_ptr;
    }

    bool Compare(const UniquePtr& other)
    {
      return m_ptr == other.m_ptr;
    }

    bool Compare(const T* ptr)
    {
      return m_ptr == ptr;
    }

  private:
    T* m_ptr;
  };

  template <class T>
  class UniquePtr<T[]>
  {
  public:
    UniquePtr()
      : m_ptr()
    {}

    explicit UniquePtr(T* ptr)
      : m_ptr(ptr)
    {}

    UniquePtr(UniquePtr&& other) noexcept
      : m_ptr(other.m_ptr)
    {
      other.m_ptr = nullptr;
    }

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
      UniquePtr<T>(MiniCRT::Move(other)).Swap(*this);
      return *this;
    }

    UniquePtr& operator=(const UniquePtr&) = delete;

   ~UniquePtr()
    {
      Reset();
    }

    void Swap(UniquePtr& other) noexcept
    {
      MiniCRT::Swap(m_ptr, other.m_ptr);
    }

    void Reset(T* ptr = nullptr) noexcept
    {
      delete [] m_ptr;
      m_ptr = ptr;
    }

    T* Get() const noexcept
    {
      return m_ptr;
    }

    explicit operator bool() const noexcept
    {
      return m_ptr != nullptr;
    }

    T& operator*() const noexcept
    {
      return *m_ptr;
    }

    T* operator->() const noexcept
    {
      return m_ptr;
    }

    T& operator[](size_t i) const
    {
      return m_ptr[i];
    }

    template<class U>
    bool Compare(const UniquePtr<U>& other)
    {
      return m_ptr == other.m_ptr;
    }

    template<class U>
    bool Compare(const U* ptr)
    {
      return m_ptr == ptr;
    }

  private:
    T* m_ptr;
  };

  template<class T, class... Args>
  EnableIfType<!IsArray<T>::value, UniquePtr<T>>
    MakeUnique(Args&&... args)
  {
    return UniquePtr<T>(new T(Forward<Args>(args)...));
  }

  template<class T>
  EnableIfType<IsArray<T>::value, UniquePtr<T>>
    MakeUnique(size_t n)
  {
    return UniquePtr<T>(new RemoveExtentType<T>[n]());
  }

  template<class T>
  class SharedPtr
  {
    struct Reference
    {
      T* m_ptr;
      int m_count;
    }*m_ref;

  public:
    SharedPtr()
      : m_ref()
    {}

    explicit SharedPtr(T* ptr)
      : m_ref()
    {
      Reset(ptr);
    }

    SharedPtr(SharedPtr&& other) noexcept
      : m_ref(other.m_ref)
    {
      other.m_ref = nullptr;
    }

    SharedPtr(const SharedPtr& other)
      : m_ref(other.m_ref)
    {
      if (m_ref)
        m_ref->m_count++;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
      SharedPtr<T>(MiniCRT::Move(other)).Swap(*this);
      return *this;
    }

    SharedPtr& operator=(const SharedPtr& other) noexcept
    {
      SharedPtr<T>(other).Swap(*this);
      return *this;
    }

   ~SharedPtr()
    {
      Reset();
    }

    void Swap(SharedPtr& other) noexcept
    {
      MiniCRT::Swap(m_ref, other.m_ref);
    }

    void Reset() noexcept
    {
      if (m_ref)
      {
        if (--m_ref->m_count == 0)
        {
          delete m_ref->m_ptr;
          delete m_ref;
        }
      }

      m_ref = nullptr;
    }

    void Reset(T* ptr) noexcept
    {
      if (m_ref)
      {
        delete m_ref->m_ptr;
        m_ref->m_ptr = ptr;
      }
      else
      {
        m_ref = new Reference;
        if (m_ref)
        {
          m_ref->m_ptr = ptr;
          m_ref->m_count = 1;
        }
      }
    }

    T* Get() const noexcept
    {
      return m_ref->m_ptr;
    }

    explicit operator bool() const noexcept
    {
      return m_ref != nullptr;
    }

    T& operator*() const noexcept
    {
      return *m_ref->m_ptr;
    }

    T* operator->() const noexcept
    {
      return m_ref->m_ptr;;
    }

    template<class U>
    bool Compare(const SharedPtr<U>& other)
    {
      return m_ref == other.m_ref && m_ref->m_ptr == other.m_ptr->m_ptr;
    }

    template<class U>
    bool Compare(const U* ptr)
    {
      return m_ref && m_ref->m_ptr == ptr;
    }
  };

  template<class T, class... Args>
  EnableIfType<!IsArray<T>::value, SharedPtr<T>>
    MakeShared(Args&&... args)
  {
    return SharedPtr<T>(new T(Forward<Args>(args)...));
  }
}
