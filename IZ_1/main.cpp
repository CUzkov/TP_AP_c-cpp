#include "lib/decimal-to-roman/decimal-to-roman.hpp"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int number = 0;

    if (!scanf("%d", &number)) {
        return 1;
    }

    char* str = (char*)calloc(15, sizeof(char));

    if (!str) {
        return 1;
    }

    str = decimal_to_roman(&number, str);

    if (!puts(str)) {
        return 1;
    }

    free(str);

    return 0;
}
