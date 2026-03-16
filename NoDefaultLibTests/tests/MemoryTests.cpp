#include <gtest/gtest.h>
#include "MiniCRT/Memory.h"

TEST(MemoryTest, TestUniquePtr)
{
	struct Foo
	{
		Foo(int b) : bar(b) {}
		int bar;
	};
	auto ptr = MiniCRT::MakeUnique<Foo>(42);
	ASSERT_TRUE(ptr);
	EXPECT_EQ(ptr->bar, 42);
}

TEST(MemoryTest, TestUniquePtrWithArray)
{
	MiniCRT::UniquePtr<char[]> ptr(new char[42]);
	ASSERT_TRUE(ptr);
	ptr[0] = 42;
	EXPECT_EQ(ptr[0], 42);
}

TEST(MemoryTest, TestUniquePtrWithArrayMake)
{
	auto ptr = MiniCRT::MakeUnique<char[]>(42);
	ASSERT_TRUE(ptr);
	ptr[0] = 42;
	EXPECT_EQ(ptr[0], 42);
}

TEST(MemoryTest, TestSharedPtr)
{
	struct Foo
	{
		Foo(int b) : bar(b) {}
		int bar;
	};
	auto ptr = MiniCRT::MakeShared<Foo>(42);
	ASSERT_TRUE(ptr);
	EXPECT_EQ(ptr->bar, 42);
}
