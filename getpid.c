#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    struct timeval start, end;
    int nloops = 1000000;

    // 시작 시간 측정
    gettimeofday(&start, NULL);

    for (int i = 0; i < nloops; i++) {
        getpid();
    }

    // 끝 시간 측정
    gettimeofday(&end, NULL);

    // 전체 걸린 시간 (마이크로초 단위)
    long diff = (end.tv_sec - start.tv_sec) * 1000000L
              + (end.tv_usec - start.tv_usec);

    // 평균 비용 계산 (마이크로초 단위)
    double avg = (double)diff / nloops;

    printf("총 실행 시간: %ld us\n", diff);
    printf("평균 getpid() 비용: %.3f us\n", avg);

    return 0;
}
