#include <gtest/gtest.h>
#include "../include/Eleven.h"

TEST(test_01, basic_test_set)
{
    Eleven a{"A1"};
    Eleven b{'0', '1', '3', '1'};
    Eleven res{"222"};
    ASSERT_TRUE(a.add(b).equals(res));
}

TEST(test_02, basic_test_set)
{
    Eleven a{"0000831A0011"};
    Eleven b{'0', '0', '0', '1', '5', '1', 'A'};
    Eleven res{"831A1530"};
    ASSERT_TRUE(a.add(b).equals(res));
}

TEST(test_03, basic_test_set)
{
    Eleven a{"00000000000"};
    Eleven b{'1'};
    Eleven res{"1"};
    ASSERT_TRUE(a.add(b).equals(res));
}

TEST(test_04, basic_test_set)
{
    Eleven a{"100123000A00"};
    Eleven b{'A', 'A', 'A', '9', '7', '9'};
    Eleven res{"100122001032"};
    ASSERT_TRUE(a.remove(b).equals(res));
}

TEST(test_05, basic_test_set)
{
    Eleven a{'A'};
    Eleven b{'0', '0', '0'};
    Eleven res{"A"};
    ASSERT_TRUE(a.remove(b).equals(res));
}

TEST(test_06, basic_test_set)
{
    Eleven a{"123501243A"};
    Eleven b{"00123501243A"};
    ASSERT_TRUE(a.equals(b) && b.equals(a));
}

TEST(test_07, basic_test_set)
{
    Eleven a{"A0031231"};
    Eleven b{"A0131231"};
    ASSERT_TRUE(!(a.equals(b) || b.equals(a)));
}

TEST(test_08, basic_test_set)
{
    Eleven a{"00012"};
    Eleven b{"0123"};
    ASSERT_TRUE(a.lt(b) && b.mt(a));
}

TEST(test_09, basic_test_set)
{
    Eleven a{"0000000"};
    Eleven b{"1"};
    ASSERT_TRUE(a.lt(b) && b.mt(a));
}

TEST(test_10, basic_test_set)
{
    Eleven a{"41239312"};
    Eleven b{"4123A312"};
    ASSERT_TRUE(a.lt(b) && b.mt(a));
}

TEST(test_11, basic_test_set)
{
    Eleven a{"00AA312"};
    Eleven b{"AA312"};
    ASSERT_TRUE(!(a.lt(b) || b.mt(a)));
}

TEST(test_12, basic_test_set)
{
    Eleven a{"83912A"};
    Eleven b{"83912A0"};
    ASSERT_TRUE(a.lt(b) && b.mt(a));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}