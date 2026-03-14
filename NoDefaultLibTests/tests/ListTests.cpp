#include <gtest/gtest.h>
#include "MiniCRT/List.h"
#include "MiniCRT/String.h"

TEST(ListTests, ConstructWithInputIteratorAndIterate)
{
  int arr[] = { 1,3,5,7,9 };
  MiniCRT::List<int> list(arr, arr + 5);

  int index = 0;
  for (auto item : list)
  {
    EXPECT_EQ(item, arr[index++]);
  }
}

TEST(ListTests, ConstructWithInitializerListAndIterate)
{
  int arr[] = { 1,3,5,7,9 };
  MiniCRT::List<int> list = { 1,3,5,7,9 };

  int index = 0;
  for (auto item : list)
  {
    EXPECT_EQ(item, arr[index++]);
  }
}

TEST(ListTests, ConstructWithInitializerListAndMoveAndIterate)
{
  int arr[] = { 1,3,5,7,9 };
  MiniCRT::List<int> list = { 1,3,5,7,9 };
  MiniCRT::List<int> list2(MiniCRT::Move(list));

  int index = 0;
  for (auto item : list2)
  {
    EXPECT_EQ(item, arr[index++]);
  }
}

TEST(ListTests, ConstructWithFillerAndIterate)
{
  MiniCRT::List<int> list((size_t)5, 1);

  for (auto item : list)
  {
    EXPECT_EQ(item, 1);
  }
}

TEST(ListTests, PopBack)
{
  int arr[] = { 1,3,5,7,0 };
  MiniCRT::List<int> list = { 1,3,5,7,9 };
  list.PopBack();

  int index = 0;
  for (auto item : list)
  {
    EXPECT_EQ(item, arr[index++]);
  }
}

TEST(ListTests, PopFront)
{
  int arr[] = { 3,5,7,9,0 };
  MiniCRT::List<int> list = { 1,3,5,7,9 };
  list.PopFront();

  int index = 0;
  for (auto item : list)
  {
    EXPECT_EQ(item, arr[index++]);
  }
}

TEST(ListTests, Size)
{
  MiniCRT::List<int> list = { 1,3,5,7,9 };
  EXPECT_EQ(list.Size(), 5);
}

TEST(ListTests, PushFront)
{
  int arr[] = { 0,1,3,5,7,0 };
  MiniCRT::List<int> list = { 1,3,5,7,9 };
  list.PushFront(0);

  int index = 0;
  for (auto item : list)
  {
    EXPECT_EQ(item, arr[index++]);
  }
}

TEST(ListTests, ConstructWithStringInitializerListAndIterate)
{
  const char* arr[] = { "01", "02", "03", "04", "05" };
  MiniCRT::List<MiniCRT::String> list = { "01", "02", "03", "04", "05" };

  int index = 0;
  for (auto item : list)
  {
    EXPECT_EQ(item, arr[index++]);
  }
}
