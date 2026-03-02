#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <fcntl.h>

#define NLOOPS 1000000

long diff_ns(struct timespec s, struct timespec e) {
    return (e.tv_sec - s.tv_sec) * 1000000000L + (e.tv_nsec - s.tv_nsec);
}

long diff_us(struct timeval s, struct timeval e) {
    return (e.tv_sec - s.tv_sec) * 1000000L + (e.tv_usec - s.tv_usec);
}

void test_getpid() {
    struct timespec s1, e1;
    struct timeval s2, e2;

    clock_gettime(CLOCK_MONOTONIC, &s1);
    for (int i = 0; i < NLOOPS; i++) getpid();
    clock_gettime(CLOCK_MONOTONIC, &e1);

    gettimeofday(&s2, NULL);
    for (int i = 0; i < NLOOPS; i++) getpid();
    gettimeofday(&e2, NULL);

    printf("getpid - clock: %.6f us\n",
           (double)diff_ns(s1, e1) / NLOOPS / 1000.0);

    printf("getpid - timeofday: %.6f us\n\n",
           (double)diff_us(s2, e2) / NLOOPS);
}

void test_read() {
    struct timespec s1, e1;
    struct timeval s2, e2;
    int fd = open("/dev/null", O_RDONLY);

    clock_gettime(CLOCK_MONOTONIC, &s1);
    for (int i = 0; i < NLOOPS; i++) read(fd, NULL, 0);
    clock_gettime(CLOCK_MONOTONIC, &e1);

    gettimeofday(&s2, NULL);
    for (int i = 0; i < NLOOPS; i++) read(fd, NULL, 0);
    gettimeofday(&e2, NULL);

    printf("read - clock: %.6f us\n",
           (double)diff_ns(s1, e1) / NLOOPS / 1000.0);

    printf("read - timeofday: %.6f us\n\n",
           (double)diff_us(s2, e2) / NLOOPS);

    close(fd);
}

int main() {
    test_getpid();
    test_read();
    return 0;
}