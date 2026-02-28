#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

int main() {
    struct timespec s, e;
    int n = 1000000;
    int fd = open("/dev/null", O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 측정 시작
    clock_gettime(CLOCK_MONOTONIC, &s);

    for (int i = 0; i < n; i++)
        read(fd, NULL, 0);

    // 측정 종료
    clock_gettime(CLOCK_MONOTONIC, &e);

    // 나노초 단위 차이 계산
    long sec = e.tv_sec - s.tv_sec;
    long nsec = e.tv_nsec - s.tv_nsec;

    double total_us = sec * 1000000.0 + nsec / 1000.0;

    printf("평균 Syscall 비용: %.3f us\n", total_us / n);

    close(fd);
    return 0;
}
