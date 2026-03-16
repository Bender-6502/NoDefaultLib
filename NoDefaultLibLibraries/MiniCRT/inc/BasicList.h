#pragma once

#include "BasicListAllocator.h"
#include "../MiniCRT/Traits.h"

namespace MiniCRT
{
  template<class T>
  struct BasicListNode
  {
    T value;
    BasicListNode* next;
    BasicListNode* previous;
  };

  template<class T, class Alloc = BasicListAllocator<BasicListNode<T>>>
  class BasicList
  {
  public:

    class Iterator
    {
      BasicListNode<T>* current;
    public:

      Iterator()
        : current(nullptr)
      {}

      Iterator(BasicListNode<T>* node)
        : current(node)
      {}

     ~Iterator()
      {}

      // Dereference operator
      T& operator*() 
      { 
        return current->value;
      }

      // Dereference const operator
      const T& operator*() const
      {
        return current->value;
      }

      // Prefix increment
      Iterator& operator++() 
      {
        if (current) 
          current = current->next;
        return *this;
      }

      // Comparison operator
      bool operator!=(const Iterator& other) const 
      {
        return current != other.current;
      }
    };

    BasicList()
      : m_head()
      , m_tail()
      , m_size()
    {}

    template <class InputIterator>
    BasicList(InputIterator first, InputIterator last)
      : m_head()
      , m_tail()
      , m_size()
    {
      Assign(first, last);
    }

    BasicList(size_t count, const T& val)
      : m_head()
      , m_tail()
      , m_size()
    {
      Assign(count, val);
    }

    BasicList(const BasicList&) = delete;

    BasicList(BasicList&& other) noexcept
      : m_head(other.m_head)
      , m_tail(other.m_tail)
      , m_size(other.m_size)
    {
      other.m_head = other.m_tail = nullptr;
      other.m_size = 0;
    }

    BasicList(std::initializer_list<T> il)
      : m_head()
      , m_tail()
      , m_size()
    {
      Assign(il.begin(), il.end());
    }

    BasicList& operator=(const BasicList&) = delete;

    BasicList& operator=(BasicList&& other) noexcept
    {
      BasicList(MiniCRT::Move(other)).Swap(*this);
      return *this;
    }

   ~BasicList()
    {
      Clear();
    }

    void Swap(BasicList& other)
    {
      MiniCRT::Swap(m_head, other.m_head);
      MiniCRT::Swap(m_tail, other.m_tail);
      MiniCRT::Swap(m_size, other.m_size);
    }

    void Clear() noexcept
    {
      for (auto* node = m_head; node != nullptr;)
      {
        auto temp = node;
        node = node->next;
        Alloc::Deallocate(temp);
      }

      m_head = m_tail = nullptr;
      m_size = 0;
    }

    template <class InputIterator>
    void Assign(InputIterator first, InputIterator last)
    {
      while (first != last)
      {
        PushBack(*first);
        first++;
      }
    }

    void Assign(size_t count, const T& val)
    {
      for (size_t i = 0; i < count; ++i)
        PushBack(val);
    }

    void PushBack(const T& value)
    {
      if (auto* node = Alloc::Allocate(); node != nullptr)
      {
        node->value = value;
        if (m_head == nullptr)
        {
          m_head = m_tail = node;
          node->next = node->previous = nullptr;
        }
        else
        {
          m_tail->next = node;
          node->previous = m_tail;
          node->next = nullptr;
          m_tail = node;
        }

        m_size++;
        node->value = value;
      }
    }

    void PushBack(T&& val)
    {
      if (auto* node = Alloc::Allocate(1); node != nullptr)
      {
        node->value = MiniCRT::Move(value);
        if (m_head == nullptr)
        {
          m_head = m_tail = node;
          node->next = node->previous = nullptr;
        }
        else
        {
          m_tail->next = node;
          node->previous = m_tail;
          node->next = nullptr;
          m_tail = node;
        }

        m_size++;
        node->value = value;
      }
    }

    void PushFront(const T& value)
    {
      if (auto* node = Alloc::Allocate(1); node != nullptr)
      {
        node->value = value;
        if (m_head == nullptr)
        {
          m_head = m_tail = node;
          node->next = node->previous = nullptr;
        }
        else
        {
          m_head->previous = node;
          m_head = node;
        }

        m_size++;
        node->value = value;
      }
    }

    void PushFront(T&& value)
    {
      if (auto* node = Alloc::Allocate(); node != nullptr)
      {
        node->value = MiniCRT::Move(value);
        if (m_head == nullptr)
        {
          m_head = m_tail = node;
          node->next = node->previous = nullptr;
        }
        else
        {
          m_head->previous = node;
          m_head = node;
        }

        m_size++;
        node->value = value;
      }
    }

    void PopBack()
    {
      if (m_tail)
      {
        if (m_head == m_tail)
        {
          Alloc::Deallocate(m_head);
          m_head = m_tail = nullptr;
          m_size = 0;
        }
        else
        {
          auto temp = m_tail;
          m_tail->previous->next = nullptr;
          m_tail = m_tail->previous;
          m_size--;
          Alloc::Deallocate(temp);
        }
      }
    }

    void PopFront()
    {
      if (m_tail)
      {
        if (m_head == m_tail)
        {
          Alloc::Deallocate(m_head);
            m_head = m_tail = nullptr;
          m_size = 0;
        }
        else
        {
          auto temp = m_head;
          m_head->next->previous = nullptr;
          m_head = m_head->next;
          m_size--;
          Alloc::Deallocate(temp);
        }
      }
    }

    Iterator begin() 
    { 
      return Iterator{ m_head }; 
    }

    Iterator end() 
    { 
      return Iterator{ nullptr }; 
    }

    /// <summary>
    /// Return the size of the list, which is the number of 
    /// entries in the list.
    /// </summary>
    /// <returns></returns>
    size_t Size() const
    {
      return m_size;
    }

  private:
    BasicListNode<T>* m_head;
    BasicListNode<T>* m_tail;
    size_t            m_size;
  };
}
