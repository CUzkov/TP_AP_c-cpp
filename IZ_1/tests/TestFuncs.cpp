#include "../lib/decimal-to-roman/decimal-to-roman.hpp"
#include <gtest/gtest.h>

TEST(decimal_to_roman, boundaryCase1)
{

    int number = 9;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("IX", decimal_to_roman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimal_to_roman, boundaryCase2)
{

    int number = 4;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("IV", decimal_to_roman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimal_to_roman, boundaryCase3)
{

    int number = 40;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("XL", decimal_to_roman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimal_to_roman, boundaryCase4)
{

    int number = 90;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("XC", decimal_to_roman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimal_to_roman, boundaryCase5)
{

    int number = 400;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("CD", decimal_to_roman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimal_to_roman, boundaryCase6)
{

    int number = 900;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("CM", decimal_to_roman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimal_to_roman, boundaryCase7)
{

    int number = 0;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("N", decimal_to_roman(&number, str)));
    ASSERT_EQ(1, number);

    free(str);
}

TEST(decimal_to_roman, boundaryCase8)
{

    int number = 6787;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("", decimal_to_roman(&number, str)));
    ASSERT_EQ(0, number);

    free(str);
}

TEST(decimal_to_roman, mainCase1)
{

    int number = 1893;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("MDCCCXCIII", decimal_to_roman(&number, str)));
    ASSERT_EQ(10, number);

    free(str);
}

TEST(decimal_to_roman, mainCase2)
{

    int number = 278;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("CCLXXVIII", decimal_to_roman(&number, str)));
    ASSERT_EQ(9, number);

    free(str);
}

TEST(decimal_to_roman, mainCase3)
{

    int number = 3001;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("MMMI", decimal_to_roman(&number, str)));
    ASSERT_EQ(4, number);

    free(str);
}

TEST(decimal_to_roman, mainCase4)
{

    int number = 1999;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("MCMXCIX", decimal_to_roman(&number, str)));
    ASSERT_EQ(7, number);

    free(str);
}

TEST(decimal_to_roman, mainCase5)
{

    int number = 23;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("XXIII", decimal_to_roman(&number, str)));
    ASSERT_EQ(5, number);

    free(str);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
