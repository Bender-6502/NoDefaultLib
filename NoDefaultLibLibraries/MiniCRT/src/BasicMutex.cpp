#include "BasicMutex.h"
#include "BasicAllocator.h"
#include "../MiniCRT/Traits.h"

#include <Windows.h>

namespace MiniCRT
{
  BasicMutex::BasicMutex()
    : m_section(Impl::Allocate(sizeof(CRITICAL_SECTION)))
  {
    InitializeCriticalSection(static_cast<LPCRITICAL_SECTION>(m_section));
  }

  BasicMutex::BasicMutex(BasicMutex&& other) noexcept
    : m_section(other.m_section)
  {
    other.m_section = nullptr;
  }

  BasicMutex& BasicMutex::operator=(BasicMutex&& other) noexcept
  {
    BasicMutex(MiniCRT::Move(other)).Swap(*this);
    return *this;
  }

  BasicMutex::~BasicMutex()
  {
    DeleteCriticalSection(static_cast<LPCRITICAL_SECTION>(m_section));
    Impl::Deallocate(m_section);
  }

  void BasicMutex::Swap(BasicMutex& other)
  {
    MiniCRT::Swap(m_section, other.m_section);
  }

  void BasicMutex::Lock()
  {
    EnterCriticalSection(static_cast<LPCRITICAL_SECTION>(m_section));
  }

  bool BasicMutex::TryLock()
  {
    return TryEnterCriticalSection(static_cast<LPCRITICAL_SECTION>(m_section)) != FALSE;
  }

  void BasicMutex::Unlock()
  {
    LeaveCriticalSection(static_cast<LPCRITICAL_SECTION>(m_section));
  }

  void* BasicMutex::NativeHandle() const
  {
    return m_section;
  }
}
