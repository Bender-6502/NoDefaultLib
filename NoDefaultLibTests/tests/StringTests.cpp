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

TEST(StringTests, ConcatenationWithEmptyString) 
{
	MiniCRT::String str1 = "Hello";
	MiniCRT::String str2;
	MiniCRT::String result = str1 + str2;
	EXPECT_EQ(result, "Hello");
	result = str2 + str1;
	EXPECT_EQ(result, "Hello");
}

TEST(StringTests, ConcatenationWithNullptr) 
{
	MiniCRT::String str1 = "Hello";
	MiniCRT::String result = str1 + static_cast<char*>(nullptr);
	EXPECT_EQ(result, "Hello");
	result = static_cast<char*>(nullptr) + str1;
	EXPECT_EQ(result, "Hello");
}

TEST(StringTests, SubStr)
{
	MiniCRT::String str = "Hello, World!";
	MiniCRT::String subStr = str.SubStr(7);
  EXPECT_EQ(subStr, "World!");
}

TEST(StringTests, SubStrOutOfBounds)
{
	MiniCRT::String str = "Hello";
	MiniCRT::String subStr = str.SubStr(10);
	EXPECT_EQ(subStr, "");
}

TEST(StringTests, SubStrEmptyString)
{
	MiniCRT::String str;
	MiniCRT::String subStr = str.SubStr(0);
	EXPECT_EQ(subStr, "");
}

TEST(StringTests, SubStrNegativeIndex)
{
	MiniCRT::String str = "Hello";
	MiniCRT::String subStr = str.SubStr(-1);
	EXPECT_EQ(subStr, "");
}

TEST(StringTests, SubStrLengthExceeds)
{
	MiniCRT::String str = "Hello";
	MiniCRT::String subStr = str.SubStr(3, 10);
	EXPECT_EQ(subStr, "lo");
}

TEST(StringTests, SubStrZeroLength)
{
	MiniCRT::String str = "Hello";
	MiniCRT::String subStr = str.SubStr(2, 0);
	EXPECT_EQ(subStr, "");
}	

TEST(StringTests, SubStrFullLength)
{
	MiniCRT::String str = "Hello";
	MiniCRT::String subStr = str.SubStr(0, 5);
	EXPECT_EQ(subStr, "Hello");
}
