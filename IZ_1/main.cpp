#include <stdio.h>
#include "lib/decimal-to-roman/decimal-to-roman.hpp"
#include <stdlib.h>


int main(void)
{
    int number = 2452;
    char* str = (char*)calloc(15, sizeof(char));

    str = (char*)decimalToRoman(&number, str);
    puts(str);

    free(str);

    return 0;
}
