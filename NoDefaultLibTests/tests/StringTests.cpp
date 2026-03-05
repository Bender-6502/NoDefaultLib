#include <gtest/gtest.h>
#include "MiniCRT/String.h"

TEST(StringTests, Concatenation) 
{
	MiniCRT::String str1 = "Hello, ";
	MiniCRT::String str2 = "World!";
	MiniCRT::String result = str1 + str2;
	EXPECT_EQ(result, "Hello, World!");
}

TEST(StringTests, Assignment) 
{
	MiniCRT::String str1 = "Hello";
	MiniCRT::String str2;
	str2 = str1;
	EXPECT_EQ(str2, "Hello");
}

TEST(StringTests, MoveAssignment) 
{
	MiniCRT::String str1 = "Hello";
	MiniCRT::String str2;
	str2 = std::move(str1);
	EXPECT_EQ(str2, "Hello");
}

TEST(StringTests, Append) 
{
	MiniCRT::String str = "Hello";
	str.Append(", World!");
	EXPECT_EQ(str, "Hello, World!");
}

TEST(StringTests, Compare) 
{
	MiniCRT::String str1 = "Hello";
	MiniCRT::String str2 = "Hello";
	MiniCRT::String str3 = "World";
	EXPECT_TRUE(str1.Compare(str2));
	EXPECT_FALSE(str1.Compare(str3));
}

TEST(StringTests, Length) 
{
	MiniCRT::String str = "Hello";
	EXPECT_EQ(str.Length(), 5);
}

TEST(StringTests, EmptyString) 
{
	MiniCRT::String str;
	EXPECT_EQ(str, "");
	EXPECT_EQ(str.Length(), 0);
}

TEST(StringTests, SelfAssignment) 
{
	MiniCRT::String str = "Hello";
	str = str;
	EXPECT_EQ(str, "Hello");
}

TEST(StringTests, SelfMoveAssignment) 
{
	MiniCRT::String str = "Hello";
	str = std::move(str);
	EXPECT_EQ(str, "Hello");
}

TEST(StringTests, NullptrAssignment) 
{
	MiniCRT::String str = "Hello";
	str = nullptr;
	EXPECT_EQ(str, "");
	EXPECT_EQ(str.Length(), 0);
}

TEST(StringTests, NullptrAppend) 
{
	MiniCRT::String str = "Hello";
	str.Append(nullptr);
	EXPECT_EQ(str, "Hello");
	EXPECT_EQ(str.Length(), 5);
}

TEST(StringTests, NullptrCompare) 
{
	MiniCRT::String str = "Hello";
	EXPECT_FALSE(str.Compare(nullptr));
}
