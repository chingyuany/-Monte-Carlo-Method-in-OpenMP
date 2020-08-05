#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int i, count = 0;
    double x, y;
    int samples;
    double pi;
    struct drand48_data randBuffer;
    samples = atoi(argv[1]);
    int nthreads = atoi(argv[2]);
    omp_set_num_threads(nthreads);

    double start = omp_get_wtime();
#pragma omp parallel if (samples > nthreads), default(none), private(i, x, y, randBuffer), shared(count, samples)
    {

        srand48_r(time(NULL) *omp_get_thread_num(), &randBuffer);

#pragma omp for nowait reduction(+:count) schedule(static, omp_get_num_threads())

        for (i = 0; i < samples; i++)
        {

            drand48_r(&randBuffer, &x);
            drand48_r(&randBuffer, &y);

            if (x * x + y * y <= 1)
            {
                count++;
            }
        }
    }
    double end = omp_get_wtime();
    printf("elapsed time %.16g\n", end - start);

    pi = 4.0 * (double)count / (double)samples;
    printf("Count = %d, samples = %d, nums of threads = %d, Estimate of pi = %7.5f\n", count, samples, nthreads, pi);
}