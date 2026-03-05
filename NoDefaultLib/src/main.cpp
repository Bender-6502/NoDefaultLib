#include "MiniCRT/String.h"
#include "MiniCRT/FileStream.h"
#include "MiniCRT/FileSystem.h"

#include <Windows.h>

// Entry point for Windows applications

// Minimum requirements
// String class
// Vector or List class
// File I/O
// Threading
// Mutexes
// Config Parser like yaml or json

int main()
{
  // String test
  MiniCRT::String message;
  message.Assign("Hello");
  message.Append(", World!");
  if (MiniCRT::String("Hello, World!") == message)
    MessageBoxA(0, message.c_str(), "SetupWorkshop", MB_OK);

  // File I/O test
  MiniCRT::CurrentDirectory("..\\x64\\Release");
  MiniCRT::FileStream file("test.txt", MiniCRT::FileStream::out | MiniCRT::FileStream::trunc);
  if (file)
  {
    const char* content = "This is a test file.";
    file.Write(content, MiniCRT::StringLength(content));
  }
  return 0;
}
