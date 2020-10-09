#include <gtest/gtest.h>
#include "../lib/decimal-to-roman/decimal-to-roman.hpp"


TEST(decimalToRoman, boundaryCase1) {

    int number = 9;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("IX", decimalToRoman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimalToRoman, boundaryCase2) {

    int number = 4;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("IV", decimalToRoman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimalToRoman, boundaryCase3) {

    int number = 40;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("XL", decimalToRoman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimalToRoman, boundaryCase4) {

    int number = 90;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("XC", decimalToRoman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimalToRoman, boundaryCase5) {

    int number = 400;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("CD", decimalToRoman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimalToRoman, boundaryCase6) {

    int number = 900;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("CM", decimalToRoman(&number, str)));
    ASSERT_EQ(2, number);

    free(str);
}

TEST(decimalToRoman, boundaryCase7) {

    int number = 0;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("N", decimalToRoman(&number, str)));
    ASSERT_EQ(1, number);

    free(str);
}

TEST(decimalToRoman, boundaryCase8) {

    int number = 6787;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("", decimalToRoman(&number, str)));
    ASSERT_EQ(0, number);

    free(str);
}

TEST(decimalToRoman, mainCase1) {

    int number = 1893;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("MDCCCXCIII", decimalToRoman(&number, str)));
    ASSERT_EQ(10, number);

    free(str);
}

TEST(decimalToRoman, mainCase2) {

    int number = 278;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("CCLXXVIII", decimalToRoman(&number, str)));
    ASSERT_EQ(9, number);

    free(str);
}

TEST(decimalToRoman, mainCase3) {

    int number = 3001;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("MMMI", decimalToRoman(&number, str)));
    ASSERT_EQ(4, number);

    free(str);
}

TEST(decimalToRoman, mainCase4) {

    int number = 1999;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("MCMXCIX", decimalToRoman(&number, str)));
    ASSERT_EQ(7, number);

    free(str);
}

TEST(decimalToRoman, mainCase5) {

    int number = 23;

    char* str = (char*)calloc(15, sizeof(char));

    ASSERT_EQ(0, strcmp("XXIII", decimalToRoman(&number, str)));
    ASSERT_EQ(5, number);

    free(str);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
