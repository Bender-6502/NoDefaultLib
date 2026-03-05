#include <gtest/gtest.h>
#include "MiniCRT/FileStream.h"
#include "MiniCRT/FileSystem.h"

TEST(FileStreamTests, OpenNonExistentFile)
{
  MiniCRT::FileStream file("non_existent_file.txt", MiniCRT::FileStream::in);
  EXPECT_FALSE(file);
}

TEST(FileStreamTests, OpenAndWriteToFile)
{
  const char* filename = "test_file.txt";
  {
    MiniCRT::FileStream file(filename, MiniCRT::FileStream::out | MiniCRT::FileStream::trunc);
    EXPECT_TRUE(file);
    const char* content = "Hello, World!";
    size_t bytesWritten = file.Write(content, strlen(content));
    EXPECT_EQ(bytesWritten, strlen(content));
  }
  {
    MiniCRT::FileStream file(filename, MiniCRT::FileStream::in);
    EXPECT_TRUE(file);
    char buffer[50];
    size_t bytesRead = file.Read(buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0'; // Null-terminate the buffer
    EXPECT_EQ(strcmp(buffer, "Hello, World!"), 0);
  }
  // Clean up
  MiniCRT::RemoveFile(filename);
}

TEST(FileStreamTests, AppendToFile)
{
  const char* filename = "test_file.txt";
  {
    MiniCRT::FileStream file(filename, MiniCRT::FileStream::out | MiniCRT::FileStream::trunc);
    EXPECT_TRUE(file);
    const char* content = "Hello";
    size_t bytesWritten = file.Write(content, strlen(content));
    EXPECT_EQ(bytesWritten, strlen(content));
  }
  {
    MiniCRT::FileStream file(filename, MiniCRT::FileStream::out | MiniCRT::FileStream::app);
    EXPECT_TRUE(file);
    const char* content = ", World!";
    size_t bytesWritten = file.Write(content, strlen(content));
    EXPECT_EQ(bytesWritten, strlen(content));
  }
  {
    MiniCRT::FileStream file(filename, MiniCRT::FileStream::in);
    EXPECT_TRUE(file);
    char buffer[50];
    size_t bytesRead = file.Read(buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0'; // Null-terminate the buffer
    EXPECT_EQ(strcmp(buffer, "Hello, World!"), 0);
  }
  // Clean up
  MiniCRT::RemoveFile(filename);
}
