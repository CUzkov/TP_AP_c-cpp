#include "counting-numbers_c.h"
#include <stdlib.h>
#include <unistd.h>

// [0] - чётные, [1] - нечётные
ssize_t* counting_sums_c(const int* const mass_numbers, size_t mass_length)
{
    ssize_t* count_masses = (ssize_t*)calloc(2, sizeof(ssize_t));
    count_masses[0] = count_masses[1] = 0;

    if (mass_numbers == NULL) {
        return count_masses;
    }

    for (size_t i = 0; i < mass_length; i++) {
        if (mass_numbers[i] % 2 == 0) {
            count_masses[0] += mass_numbers[i];
        } else {
            count_masses[1] += mass_numbers[i];
        }
    }

    return count_masses;
}
