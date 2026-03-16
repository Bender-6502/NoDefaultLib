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

  /// <summary>
  /// Forwards the LValue referencce
  /// </summary>
  /// <typeparam name="T"></typeparam>
  /// <param name="Arg"></param>
  /// <returns></returns>
  template <class T>
  inline T&& Forward(typename RemoveReference<T>::Type& Arg) noexcept
  {
    return static_cast<T&&>(Arg);
  }

  /// <summary>
  /// Forwards the LValue referencce
  /// </summary>
  /// <typeparam name="T"></typeparam>
  /// <param name="Arg"></param>
  /// <returns></returns>
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


  template <class T>
  struct RemoveExtent { // remove array extent
    using type = T;
  };

  template <class T, size_t size>
  struct RemoveExtent<T[size]> {
    using type = T;
  };

  template <class T>
  struct RemoveExtent<T[]> {
    using type = T;
  };

  template <class T>
  using RemoveExtentType = typename RemoveExtent<T>::type;


  template <class T, T val>
    struct IntegralConstant {
    static constexpr T value = val;

    using value_type = T;
    using type = IntegralConstant;

    constexpr operator value_type() const noexcept 
    {
      return value;
    }

    constexpr value_type operator()() const noexcept 
    {
      return value;
    }
  };

  template <bool val>
    using BoolConstant = IntegralConstant<bool, val>;


  template <class>
    constexpr bool IsArrayVar = false;

  template <class T, size_t size>
  constexpr bool IsArrayVar<T[size]> = true;

  template <class T>
  constexpr bool IsArrayVar<T[]> = true;

  template <class T>
    struct IsArray : BoolConstant<IsArrayVar<T>> {};

  template <bool T, class U = void>
    struct EnableIf {};


  template <class T>
  struct EnableIf<true, T> 
  {
    using type = T;
  };

  template <bool T, class U = void>
    using EnableIfType = typename EnableIf<T, U>::type;
}
