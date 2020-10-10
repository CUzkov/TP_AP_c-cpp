extern "C" {
#include "../lib/decimal-to-roman/decimal-to-roman.h"
}
#include <gtest/gtest.h>

class TestDecimalToRoman : public ::testing::Test {
protected:
    void SetUp()
    {
    }
    void TearDown()
    {
        free(str);
    }
    int lenth = 0;
    char* str;
};

TEST_F(TestDecimalToRoman, boundaryCaseNine)
{
    str = decimal_to_roman(9, &lenth);
    EXPECT_EQ(0, strcmp("IX", str));
    EXPECT_EQ(2, lenth);
}

TEST_F(TestDecimalToRoman, boundaryCaseFour)
{
    str = decimal_to_roman(4, &lenth);
    EXPECT_EQ(0, strcmp("IV", str));
    EXPECT_EQ(2, lenth);
}

TEST_F(TestDecimalToRoman, boundaryCaseFourty)
{
    str = decimal_to_roman(40, &lenth);
    EXPECT_EQ(0, strcmp("XL", str));
    EXPECT_EQ(2, lenth);
}

TEST_F(TestDecimalToRoman, boundaryCaseNinety)
{
    str = decimal_to_roman(90, &lenth);
    EXPECT_EQ(0, strcmp("XC", str));
    EXPECT_EQ(2, lenth);
}

TEST_F(TestDecimalToRoman, boundaryCaseFourHundred)
{
    str = decimal_to_roman(400, &lenth);
    EXPECT_EQ(0, strcmp("CD", str));
    EXPECT_EQ(2, lenth);
}

TEST_F(TestDecimalToRoman, boundaryCaseNineHundred)
{
    str = decimal_to_roman(900, &lenth);
    EXPECT_EQ(0, strcmp("CM", str));
    EXPECT_EQ(2, lenth);
}

TEST_F(TestDecimalToRoman, boundaryCaseZero)
{
    str = decimal_to_roman(0, &lenth);
    EXPECT_EQ(0, strcmp("N", str));
    EXPECT_EQ(1, lenth);
}

TEST_F(TestDecimalToRoman, boundaryCaseExceedValue)
{
    str = decimal_to_roman(6787, &lenth);
    EXPECT_EQ(0, strcmp("", str));
    EXPECT_EQ(0, lenth);
}

TEST_F(TestDecimalToRoman, mainCaseValue1893)
{
    str = decimal_to_roman(1893, &lenth);
    EXPECT_EQ(0, strcmp("MDCCCXCIII", str));
    EXPECT_EQ(10, lenth);
}

TEST_F(TestDecimalToRoman, mainCaseValue278)
{
    str = decimal_to_roman(278, &lenth);
    EXPECT_EQ(0, strcmp("CCLXXVIII", str));
    EXPECT_EQ(9, lenth);
}

TEST_F(TestDecimalToRoman, mainCaseValue3001)
{
    str = decimal_to_roman(3001, &lenth);
    EXPECT_EQ(0, strcmp("MMMI", str));
    EXPECT_EQ(4, lenth);
}

TEST_F(TestDecimalToRoman, mainCaseValue1999)
{
    str = decimal_to_roman(1999, &lenth);
    EXPECT_EQ(0, strcmp("MCMXCIX", str));
    EXPECT_EQ(7, lenth);
}

TEST_F(TestDecimalToRoman, mainCaseValue23)
{
    str = decimal_to_roman(23, &lenth);
    EXPECT_EQ(0, strcmp("XXIII", str));
    EXPECT_EQ(5, lenth);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
