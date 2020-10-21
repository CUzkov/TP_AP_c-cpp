extern "C" {
#include "../lib/counting-numbers_c/counting-numbers_c.h"
}
#include <gtest/gtest.h>
#include <dlfcn.h>

class TestCN_C : public ::testing::Test {
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

class TestCN_P : public ::testing::Test {
protected:
    void SetUp()
    {
        _library = dlopen("./libC_N_P.so", RTLD_NOW);
        *(void **) (&counting_sums_p) = dlsym(_library, "counting_sums_p");
        for (size_t i = 0; i < 10; i++) {
            _mass_numbers[i] = i;
        }
    }
    void TearDown()
    {
        dlclose(_library);
        free(_mass_c);
    }
    void* _library = 0;
    ssize_t* (*counting_sums_p)(int* mass_numbers, size_t mass_length, size_t threads_number);
    int _mass_numbers[10];
    ssize_t* _mass_c;
};

TEST_F(TestCN_C, usuallTest)
{
    _mass_c = counting_sums_c(_mass_numbers, 10);
    EXPECT_EQ(_mass_c[0], 20);
    EXPECT_EQ(_mass_c[1], 25);
}

TEST_F(TestCN_C, NULLToFunc)
{
    _mass_c = counting_sums_c(NULL, 10);
    EXPECT_EQ(_mass_c[0], 0);
    EXPECT_EQ(_mass_c[1], 0);
}

TEST_F(TestCN_P, usuallTest)
{
    _mass_c = (*counting_sums_p)(_mass_numbers, 10, 4);
    EXPECT_EQ(_mass_c[0], 20);
    EXPECT_EQ(_mass_c[1], 25);
}

TEST_F(TestCN_P, NULLToFunc)
{
    _mass_c = (*counting_sums_p)(NULL, 10, 4);
    EXPECT_EQ(_mass_c[0], 0);
    EXPECT_EQ(_mass_c[1], 0);
}

TEST_F(TestCN_P, ZeroThreads)
{
    _mass_c = (*counting_sums_p)(_mass_numbers, 10, 0);
    EXPECT_EQ(_mass_c[0], 20);
    EXPECT_EQ(_mass_c[1], 25);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
