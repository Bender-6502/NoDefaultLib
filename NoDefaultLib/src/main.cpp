#include "MiniCRT/String.h"
#include "MiniCRT/FileStream.h"
#include "MiniCRT/FileSystem.h"
#include "MiniCRT/Thread.h"
#include "MiniCRT/Mutex.h"
#include "MiniCRT/Memory.h"

#include <Windows.h>

namespace MiniCRT
{
  extern int alloc_counter;
}

struct ThreadHandler
{
  MiniCRT::Mutex* mutex;
  const char* message;
};

void ThreadedMessage(void* message)
{
  MiniCRT::LockGuard lock(*static_cast<ThreadHandler*>(message)->mutex);
  MessageBoxA(0, static_cast<ThreadHandler*>(message)->message, "NoDefaultLib", MB_OK);
}

// Entry point for Windows applications
int main()
{
  {
    // String test
    MiniCRT::String message;
    message.Assign("Hello");
    message.Append(", World!");

    MiniCRT::Mutex mutex;
    ThreadHandler threadHandler1{ &mutex, message.c_str() };
    MiniCRT::Thread th(&ThreadedMessage, &threadHandler1);
    ThreadHandler threadHandler2{ &mutex, "Goodbye, world!" };
    ThreadedMessage(&threadHandler2);

    // File I/O test
    MiniCRT::CurrentDirectory("..\\x64\\Release");
    MiniCRT::FileStream file("test.txt", MiniCRT::FileStream::out | MiniCRT::FileStream::trunc);
    if (file)
    {
      const char* content = "This is a test file.";
      file.Write(content, MiniCRT::StringLength(content));
    }

    char* c = new char[256];
    delete[] c;
  }

  // Test for memory leaks
  if (MiniCRT::HasMemoryLeaks())
  {
    auto temp = MiniCRT::MemoryLeakCount();
    MiniCRT::String message("Memory leaks detected: ");
    message += MiniCRT::ToString(temp);

    MessageBoxA(0, message.c_str(), "NoDefaultLib", MB_OK);
  }

  return 0;
}
