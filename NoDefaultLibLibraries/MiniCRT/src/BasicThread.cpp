#include "BasicThread.h"
#include "../MiniCRT/Traits.h"

#include <Windows.h>

namespace MiniCRT
{
  BasicThread::BasicThread()
    : m_thread(nullptr)
    , m_id()
  {}

  BasicThread::BasicThread(Function&& func, void* arg)
    : m_thread(nullptr)
    , m_id(0)
    , m_function(func)
    , m_arg(arg)
  {
    m_thread = reinterpret_cast<void*>(::CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&StartRoutine), this, 0, &m_id));
  }

  BasicThread::BasicThread(BasicThread&& other) noexcept
    : m_thread(other.m_thread)
    , m_id(other.m_id)
  {
    other.m_thread = nullptr;
    other.m_id = 0;
  }

  BasicThread& BasicThread::operator=(BasicThread&& other) noexcept
  {
    BasicThread(MiniCRT::Move(other)).Swap(*this);
    return *this;
  }

  BasicThread::~BasicThread()
  {
    if (IsJoinable())
      Join();
  }

  void BasicThread::Swap(BasicThread& other)
  {
    MiniCRT::Swap(m_thread, other.m_thread);
    MiniCRT::Swap(m_id, other.m_id);
  }

  bool BasicThread::IsJoinable() const
  {
    return m_thread != nullptr;
  }

  void BasicThread::Join()
  {
    if (m_thread)
    {
      ::WaitForSingleObject(m_thread, INFINITE);
      Detach();
    }
  }

  void BasicThread::Detach()
  {
    if (m_thread)
      ::CloseHandle(m_thread);
    m_thread = nullptr;

  }

  void* BasicThread::NativeHandle() const
  {
    return m_thread;
  }

  unsigned long BasicThread::StartRoutine(BasicThread* obj)
  {
    obj->m_function(obj->m_arg);
    return 0;
  }
}
