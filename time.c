#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

long get_time_in_milliseconds(void) {
    struct timeval start;
    gettimeofday(&start, NULL);
    long milliseconds = (long)(start.tv_sec * 1000 + start.tv_usec / 1000);
    return milliseconds;
}

long calculate_time_difference(long start_time, long end_time) {
    return end_time - start_time;
}

int main() {
	long	start_time;
	long	end_time;

    start_time = get_time_in_milliseconds();
	usleep(5000);
    end_time = get_time_in_milliseconds();

    long time_difference = calculate_time_difference(start_time, end_time);
    printf("Diferencia de tiempo: %ld milisegundos\n", time_difference);

    return 0;
}
