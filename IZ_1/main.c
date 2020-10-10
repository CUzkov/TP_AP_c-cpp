#include "lib/decimal-to-roman/decimal-to-roman.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int number = 0;

    if (!scanf("%d", &number)) {
        return EXIT_FAILURE;
    }

    int lenth = 0;

    char* str = decimal_to_roman(number, &lenth);

    if (str == NULL) {
        return EXIT_FAILURE;
    }

    if (!puts(str)) {
        return EXIT_FAILURE;
    }

    free(str);

    return EXIT_SUCCESS;
}
