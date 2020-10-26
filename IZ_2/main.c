#include "lib/counting-numbers_c/counting-numbers_c.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

extern char* optarg;
extern int optind, opterr, optopt;

#define TEN_KK 10000000

int load_file(char* file_path, int* mass, size_t position, size_t count) {
    
    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        return -1;
    }

    for (int j = 0; j < count; j++) {
        int buffer = 0;
        if (!fscanf(file, "%d", &buffer)) {
            return -1;
        }
        mass[j] = buffer;
    }

    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}

int main(int argc, char** argv)
{
    char* opts = "t:n:f:";
    char* file_path = "";
    size_t threads_number = 2, numbers_number = 1;
    int opt;
    ssize_t buffer = 0;

    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
        case 't':
            if ((buffer = atoi(optarg)) == 0) {
                if (!puts("Значение флага -t обязателено\n")) {
                    return EXIT_FAILURE;
                };
                return EXIT_FAILURE;
            }

            if (buffer < 0) {
                if (!puts("Число потоков должно быть больше нуля\n")) {
                    return EXIT_FAILURE;
                };
                return EXIT_FAILURE;
            }

            threads_number = buffer;
            break;
        case 'n':
            if ((buffer = atoi(optarg)) == 0) {
                if (!puts("Значение флага -n обязателено\n")) {
                    return EXIT_FAILURE;
                };
                return EXIT_FAILURE;
            }

            if (buffer <= 0) {
                if (!puts("Число чисел должно быть больше нуля\n")) {
                    return EXIT_FAILURE;
                };
                return EXIT_FAILURE;
            }

            numbers_number = buffer;
            break;
        case 'f':
            file_path = optarg;
            break;

        default:
            break;
        }
    }

    struct timespec start, finish;
    double elapsed;

    void* library = 0;
    ssize_t* (*counting_sums_p)(int* mass_numbers, size_t mass_length, size_t threads_number);

    library = dlopen("./libCOUNTING_NUMBERS_THREADS.so", RTLD_NOW);

    if (!library) {
        printf("%s", "Библиотека libCOUNTING_NUMBERS_THREADS.so не найдена");
        return EXIT_FAILURE;
    }

    *(void**)(&counting_sums_p) = dlsym(library, "counting_sums_p");

    ssize_t sum_mass_p[2] = {0, 0};
    ssize_t sum_mass_c[2] = {0, 0};
    float times[2] = {0, 0};
    const int number_of_iters = (numbers_number / TEN_KK + 1);
    int* mass_numbers;

    long l1dcls = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    size_t numbers_in_iter = ((number_of_iters == 1) ? numbers_number : TEN_KK);

    if (l1dcls == -1) {
        l1dcls = sizeof(void*);
    }

    int errflag = posix_memalign((void**)&mass_numbers, l1dcls, sizeof(int) * numbers_in_iter);

    if (errflag) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < number_of_iters; i++) {
        
        numbers_in_iter = ((i == number_of_iters) ? numbers_number - TEN_KK * i : TEN_KK);
        numbers_in_iter = ((number_of_iters == 1) ? numbers_number : TEN_KK);

        int errflag = load_file(file_path, mass_numbers, TEN_KK * i, numbers_in_iter);

        if (errflag == -1) {
            if (!puts("Ошибка причтении или открытии файла")) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }

        if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &start) == -1) {
            return EXIT_FAILURE;
        };

        ssize_t* mass_p = (*counting_sums_p)(mass_numbers, numbers_in_iter, threads_number);

        if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &finish) == -1) {
            return EXIT_FAILURE;
        }

        sum_mass_p[0] += mass_p[0];
        sum_mass_p[1] += mass_p[1];

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        times[0] += elapsed;

        if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &start) == -1) {
            return EXIT_FAILURE;
        };

        ssize_t* mass_c = counting_sums_c(mass_numbers, numbers_in_iter);

        if (clock_gettime(_POSIX_MONOTONIC_CLOCK, &finish) == -1) {
            return EXIT_FAILURE;
        };

        sum_mass_c[0] += mass_c[0];
        sum_mass_c[1] += mass_c[1];

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

        times[1] += elapsed;

        if (
            mass_c[0] != mass_p[0] &&
            mass_c[1] != mass_p[1]
        ) {
            if (!puts("Промежуточные значения сумм для разных алгоритмов не совпадают.")) {
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }

        free(mass_p);
        free(mass_c);
    }

    free(mass_numbers);

    printf("Многопоточная реализация: %fs\n", times[0]);
    printf("Сумма чётный и нечётных чисел соответственно: %zu %zu\n", sum_mass_p[0], sum_mass_p[1]);
    printf("Последовательная реализация реализация: %fs\n", times[1]);
    printf("Сумма чётный и нечётных чисел соответственно: %zu %zu\n", sum_mass_c[0], sum_mass_c[1]);

    dlclose(library);

    return EXIT_SUCCESS;
}