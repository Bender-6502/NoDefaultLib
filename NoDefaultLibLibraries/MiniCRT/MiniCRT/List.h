#pragma once
#include "BasicList.h"

namespace MiniCRT
{
  template<class T, class Alloc = BasicAllocator<BasicListNode<T>>>
  class List : public BasicList<T, Alloc>
  {
  public:
    using Iterator = BasicList<T, Alloc>::Iterator;

    List()
      : BasicList()
    {}

    template <class InputIterator>
    List(InputIterator first, InputIterator last)
      : BasicList(first, last)
    {}

    List(size_t count, const T& val)
      : BasicList(count, val)
    {}

    List(const List&) = delete;

    List(List&& other) noexcept
      : BasicList(MiniCRT::Move(other))
    {}

    List(std::initializer_list<T> il)
      : BasicList(il)
    {}

    List& operator=(const List&) = delete;

    List& operator=(List&& other) noexcept
    {
      return BasicList<T, Alloc>::operator=(MiniCRT::Move(other));
    }

   ~List()
    {}
  };
}
