#pragma once

namespace MiniCRT
{
  template<class T>
  struct RemoveReference
  {
    typedef T Type;
  };

  template<class T>
  struct RemoveReference<T&>
  {
    typedef T Type;
  };

  template<class T>
  struct RemoveReference<T&&>
  {
    typedef T Type;
  };

  template<class T> 
  inline typename RemoveReference<T>::Type&& Move(T&& Arg)
  {
    return static_cast<typename RemoveReference<T>::Type&&>(Arg);
  }

  template<class T> 
  inline void Swap(T& t1, T& t2) 
  {
    T tmp(t1);
    t1 = t2;
    t2 = tmp;
  }
}
