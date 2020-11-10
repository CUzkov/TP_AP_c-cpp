#include "counting-numbers_p.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;

typedef struct mass_area_tag {
    int* mass_numbers;
    size_t first_index;
    size_t second_index;
    ssize_t* count_masses;
} mass_area_t;

void* counting_thread(void* arg)
{
    mass_area_t* args = (mass_area_t*)arg;

    ssize_t mass_buffer[2] = { 0, 0 };

    for (size_t i = args->first_index; i < args->second_index; i++) {
        if (args->mass_numbers[i] % 2 == 0) {
            mass_buffer[0] += args->mass_numbers[i];
        } else {
            mass_buffer[1] += args->mass_numbers[i];
        }
    }

    pthread_mutex_lock(&mutex);

    args->count_masses[0] += mass_buffer[0];
    args->count_masses[1] += mass_buffer[1];

    pthread_mutex_unlock(&mutex);

    return arg;
}

ssize_t* counting_sums_p(int* mass_numbers, size_t mass_length, size_t threads_number)
{
    ssize_t* count_masses = (ssize_t*)calloc(2, sizeof(ssize_t));
    count_masses[0] = count_masses[1] = 0;

    if (mass_numbers == NULL) {
        return count_masses;
    }

    if (threads_number == 0) {
        threads_number = sysconf(_SC_NPROCESSORS_ONLN);
    }

    size_t area_length = mass_length / threads_number;
    if (area_length < threads_number) {
        threads_number = 1;
    }

    pthread_t threads[threads_number];
    mass_area_t args[threads_number];
    int errflags[threads_number];

    pthread_mutex_init(&mutex, NULL);

    for (size_t i = 0; i < threads_number; i++) {

        args[i].first_index = i * area_length;
        args[i].second_index = (i == threads_number - 1) ? mass_length : ((i + 1) * area_length);
        args[i].mass_numbers = mass_numbers;
        args[i].count_masses = count_masses;

        errflags[i] = pthread_create(
            &threads[i],
            NULL,
            counting_thread,
            (void*)&args[i]);

        if (errflags[i] != 0) {
        }
    }

    for (size_t i = 0; i < threads_number; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return count_masses;
}
