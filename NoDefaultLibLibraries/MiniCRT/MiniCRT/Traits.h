#pragma once

namespace MiniCRT
{
  /// <summary>
  /// Remove reference qualifiers from a type. This primary template handles 
  /// types that are not references, leaving them unchanged.
  /// </summary>
  /// <typeparam name="T"></typeparam>
  template<class T>
  struct RemoveReference
  {
    typedef T Type;
  };

  /// <summary>
  /// Remove reference qualifiers from a type. This specialization handles 
  /// lvalue references, which are denoted by T&. 
  /// </summary>
  /// <typeparam name="T"></typeparam>
  template<class T>
  struct RemoveReference<T&>
  {
    typedef T Type;
  };

  /// <summary>
  /// Remove reference qualifiers from a type. This specialization handles 
  /// rvalue references, which are denoted by T&&.
  /// </summary>
  /// <typeparam name="T"></typeparam>
  template<class T>
  struct RemoveReference<T&&>
  {
    typedef T Type;
  };

  /// <summary>
  /// Move the specified argument, allowing it to be treated as an rvalue.
  /// </summary>
  /// <typeparam name="T"></typeparam>
  /// <param name="Arg"></param>
  /// <returns></returns>
  template<class T> 
  inline typename RemoveReference<T>::Type&& Move(T&& Arg)
  {
    return static_cast<typename RemoveReference<T>::Type&&>(Arg);
  }

  template <class T>
  inline T&& Forward(typename RemoveReference<T>::Type& Arg) noexcept
  {
    return static_cast<T&&>(Arg);
  }

  template <class T>
  inline T&& Forward(typename RemoveReference<T>::Type&& Arg) noexcept
  {
    return static_cast<T&&>(Arg);
  }

  /// <summary>
  /// Swwap the values of two variables.
  /// </summary>
  /// <typeparam name="T"></typeparam>
  /// <param name="t1"></param>
  /// <param name="t2"></param>
  template<class T> 
  inline void Swap(T& t1, T& t2) 
  {
    T tmp(t1);
    t1 = t2;
    t2 = tmp;
  }
}
