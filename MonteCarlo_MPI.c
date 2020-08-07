#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int i, count, total_count, partitial_sample;
    double x, y;
    int samples;
    double pi, start, end;
    int rank, numtasks;
    samples = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    partitial_sample = samples / numtasks;
    count = 0;
    start = MPI_Wtime();

    for (i = 0; i < partitial_sample; i++)
    {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1)
            count++;
    }

    total_count = count;

    MPI_Reduce(&count, &total_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("The total sum of all counts at process %d is %d \n", rank, total_count);
    if (rank == 0)
    {

        pi = 4.0 * (double)total_count / (double)samples;
        end = MPI_Wtime();
        printf("total count = %d, Samples = %d, Estimate of pi = %7.5f Elapsed time = %7.5f \n", total_count, samples, pi, end - start);
    }
    MPI_Finalize();
    //return 0;
}