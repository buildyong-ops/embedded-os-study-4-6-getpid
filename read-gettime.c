#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

#define ITERATIONS 1000000

double time_diff_us(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000.0 +
           (end.tv_usec - start.tv_usec);
}

int main() {
    struct timeval start, end;
    double elapsed;

    int fd = open("/dev/null", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 측정 시작
    gettimeofday(&start, NULL);

    for (int i = 0; i < ITERATIONS; i++) {
        read(fd, NULL, 0);
    }

    // 측정 종료
    gettimeofday(&end, NULL);

    elapsed = time_diff_us(start, end);

    printf("read(fd, NULL, 0) 총 시간: %f us\n", elapsed);
    printf("read(fd, NULL, 0) 평균 시간: %f us\n", elapsed / ITERATIONS);

    close(fd);

    return 0;
}
