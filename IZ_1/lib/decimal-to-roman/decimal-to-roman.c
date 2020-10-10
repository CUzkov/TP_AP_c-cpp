#include "decimal-to-roman.h"
#include <stdio.h>
#include <stdlib.h>

char* decimal_to_roman(int number, int* const length)
{
    if (length == NULL) {
        char* str = (char*)calloc(1, sizeof(char));
        return str;
    }

    if (number > 3999 || number < 0) {
        *length = 0;
        char* str = (char*)calloc(1, sizeof(char));
        return str;
    }

    if (number == 0) {
        char* str = (char*)calloc(2, sizeof(char));
        str[0] = 'N';
        *length = 1;
        return str;
    }

    char roman_chars[7] = { 'M', 'D', 'C', 'L', 'X', 'V', 'I' };
    int divider = 1000;
    int mass_ptr = 0;
    int divider_iteration_count = 0;
    // Буффер с текущим и предыдущим количеством букв
    int buffers[2] = { 0, 0 };

    char* str = (char*)calloc(15, sizeof(char));

    if (!str) {
        return NULL;
    }

    while (number >= 1) {
        buffers[0] = number / divider;

        if (buffers[0] != 0) {
            if (buffers[0] == 4 && buffers[1] == 1) {
                str[mass_ptr - 1] = roman_chars[divider_iteration_count];
                str[mass_ptr] = roman_chars[divider_iteration_count - 2];
                mass_ptr++;
            } else if (buffers[0] == 4) {
                str[mass_ptr] = roman_chars[divider_iteration_count];
                str[mass_ptr + 1] = roman_chars[divider_iteration_count - 1];
                mass_ptr += 2;
            } else {
                for (int i = 0; i < buffers[0]; i++) {
                    str[mass_ptr] = roman_chars[divider_iteration_count];
                    mass_ptr++;
                }
            }
        }

        number %= divider;
        divider = (divider_iteration_count % 2 == 0) ? divider / 2 : divider / 5;
        divider_iteration_count++;
        buffers[1] = buffers[0];
    }

    char* str_return = (char*)realloc(str, mass_ptr);
    *length = mass_ptr;

    return str_return;
}
