#include <Windows.h>

namespace MiniCRT
{
  namespace
  {
    static int alloc_counter = 0;
  }

  bool HasMemoryLeaks()
  {
    return alloc_counter > 0;
  }

  int MemoryLeakCount()
  {
    return alloc_counter;
  }
}

void* operator new(size_t size)
{
  MiniCRT::alloc_counter++;
  return ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void* operator new[](size_t size)
{
  MiniCRT::alloc_counter++;
  return ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

void operator delete(void* ptr)
{
  if (ptr)
  {
    ::HeapFree(::GetProcessHeap(), 0, ptr);
    MiniCRT::alloc_counter--;
  }
}

void operator delete(void*, void*) // placement, do nothing
{}

void operator delete(void* ptr, unsigned __int64)
{
  if (ptr)
  {
    ::HeapFree(::GetProcessHeap(), 0, ptr);
    MiniCRT::alloc_counter--;
  }
}

void operator delete[](void* ptr)
{
  if (ptr)
  {
    ::HeapFree(::GetProcessHeap(), 0, ptr);
    MiniCRT::alloc_counter--;
  }
}

void operator delete[](void*, void*) // placement, do nothing
{
}

void operator delete[](void* ptr, unsigned __int64)
{
  if (ptr)
  {
    ::HeapFree(::GetProcessHeap(), 0, ptr);
    MiniCRT::alloc_counter--;
  }
}
