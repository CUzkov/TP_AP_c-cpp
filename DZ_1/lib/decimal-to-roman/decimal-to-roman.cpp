#include "decimal-to-roman.hpp"
#include <stdlib.h> 


char* decimalToRoman(int* number, char* str)
{
    if(*number > 3999 || *number < 0) {
        *number = 0;
        return str;
    }
    
    if(*number == 0) {
        str[0] = 'N';
        *number = 1;
        return str;
    }

    char roman_chars[7] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    int divider = 1000;
    int mass_ptr = 0;
    int divider_iteration_count = 0;
    // Буффер с текущим и предыдущим количеством букв
    int buffers[2] = {0, 0};

    while(*number >= 1)
    {
        buffers[0] = *number / divider;

        if(buffers[0] != 0) {
            if(buffers[0] == 4 && buffers[1] == 1) {
                str[mass_ptr - 1] = roman_chars[divider_iteration_count];
                str[mass_ptr] = roman_chars[divider_iteration_count - 2];
                mass_ptr++;
            }
            else if(buffers[0] == 4) {
                str[mass_ptr] = roman_chars[divider_iteration_count];
                str[mass_ptr + 1] = roman_chars[divider_iteration_count - 1];
                mass_ptr += 2;
            }
            else
            {
                for(int i = 0; i < buffers[0]; i++)
                {
                    str[mass_ptr] = roman_chars[divider_iteration_count];
                    mass_ptr++;
                }
            }
        }

        *number %= divider;
        divider = (divider_iteration_count % 2 == 0) ? divider / 2 : divider / 5;
        divider_iteration_count++;
        buffers[1] = buffers[0];
    }

    *number = mass_ptr;

    return str;
}
