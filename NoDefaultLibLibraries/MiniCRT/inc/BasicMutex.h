#pragma once
#include <Windows.h>
#include "../MiniCRT/Traits.h"

namespace MiniCRT
{
  class BasicMutex
  {
  public:
    BasicMutex();
    BasicMutex(const BasicMutex&) = delete;
    BasicMutex(BasicMutex&& other) noexcept;
    BasicMutex& operator=(const BasicMutex&) = delete;
    BasicMutex& operator=(BasicMutex&&) noexcept;
   ~BasicMutex();

    void Swap(BasicMutex& other);

    /// <summary>
    /// Locks the mutex
    /// </summary>
    void Lock();

    /// <summary>
    /// Tries to lock the mutex
    /// </summary>
    /// <returns>true if lock successful</returns>
    bool TryLock();

    /// <summary>
    /// Unlocks the mutex
    /// </summary>
    void Unlock();

    /// <summary>
    /// Returns the handle to the mutex
    /// </summary>
    /// <returns></returns>
    void* NativeHandle() const;

  private:
    void* m_section;
  };
}
