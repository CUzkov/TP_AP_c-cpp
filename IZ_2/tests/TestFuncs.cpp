extern "C" {
#include "../lib/counting-numbers_c/counting-numbers_c.h"
#include "../lib/counting-numbers_p/counting-numbers_p.h"
}
#include <gtest/gtest.h>
#include <dlfcn.h>

#ifndef SOURCE_DIR
    #define SOURCE_DIR ""
#endif
#ifndef NUMBER_NUMBERS
    #define NUMBER_NUMBERS 0
#endif

class TestLibCountingNumbers : public ::testing::Test {
protected:
    void SetUp()
    {
        for (size_t i = 0; i < 10; i++) {
            _mass_numbers[i] = i;
        }
    }
    void TearDown()
    {
        free(_mass_c);
    }
    int _mass_numbers[10];
    ssize_t* _mass_c;
};

class TestLibCountingNumbersThreads : public ::testing::Test {
protected:
    void SetUp()
    {
        for (size_t i = 0; i < 10; i++) {
            _mass_numbers[i] = i;
        }
    }
    void TearDown()
    {
        free(_mass_c);
    }
    int _mass_numbers[10];
    ssize_t* _mass_c;
};

class TestLibs : public ::testing::Test {
protected:
    void SetUp()
    {
        FILE* file = fopen(SOURCE_DIR"/tmp/text.txt", "r");

        if (file == NULL) {
            puts("Не удалось открыть файл");
            exit(1);
        }

        for (int j = 0; j < NUMBER_NUMBERS; j++) {
            int buffer = 0;
            fscanf(file, "%d", &buffer);
            _mass_numbers[j] = buffer;
        }

        fclose(file);
    }
    void TearDown()
    {
        free(_mass_c);
        free(_mass_p);
    }
    int _mass_numbers[NUMBER_NUMBERS];
    ssize_t* _mass_c;
    ssize_t* _mass_p;
};

TEST_F(TestLibCountingNumbers, usuallTest)
{
    _mass_c = counting_sums_c(_mass_numbers, 10);
    EXPECT_EQ(_mass_c[0], 20);
    EXPECT_EQ(_mass_c[1], 25);
}

TEST_F(TestLibCountingNumbers, NULLToFunc)
{
    _mass_c = counting_sums_c(NULL, 10);
    EXPECT_EQ(_mass_c[0], 0);
    EXPECT_EQ(_mass_c[1], 0);
}

TEST_F(TestLibCountingNumbersThreads, usuallTest)
{
    _mass_c = counting_sums_p(_mass_numbers, 10, 4);
    EXPECT_EQ(_mass_c[0], 20);
    EXPECT_EQ(_mass_c[1], 25);
}

TEST_F(TestLibCountingNumbersThreads, NULLToFunc)
{
    _mass_c = counting_sums_p(NULL, 10, 4);
    EXPECT_EQ(_mass_c[0], 0);
    EXPECT_EQ(_mass_c[1], 0);
}

TEST_F(TestLibCountingNumbersThreads, ZeroThreads)
{
    _mass_c = counting_sums_p(_mass_numbers, 10, 0);
    EXPECT_EQ(_mass_c[0], 20);
    EXPECT_EQ(_mass_c[1], 25);
}

TEST_F(TestLibs, BigData)
{
    _mass_p = counting_sums_p(_mass_numbers, NUMBER_NUMBERS, 0);
    _mass_c = counting_sums_c(_mass_numbers, NUMBER_NUMBERS);
    EXPECT_EQ(_mass_c[0], _mass_p[0]);
    EXPECT_EQ(_mass_c[1], _mass_p[1]);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
