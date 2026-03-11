#pragma once
#include "BasicMutex.h"

namespace MiniCRT
{
  using Mutex = BasicMutex;

  class LockGuard
  {
  public:
    LockGuard(Mutex& mutex) : m_mutex(mutex) { m_mutex.Lock(); }
   ~LockGuard() { m_mutex.Unlock(); }

  private:
    Mutex& m_mutex;
  };
}
