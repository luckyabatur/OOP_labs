#include <gtest/gtest.h>
#include "../include/delete_letters.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(delete_letters("")=="");
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(delete_letters("asdbgh123.3134")=="");
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(delete_letters("123sadsadsa345234affASDSAFd873dsa2")=="123 345234 873 2");
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(delete_letters("111")=="111");
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(delete_letters("dsAdasAasdOOIKDadasd")=="");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}