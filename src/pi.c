/*
Parallel calculation of π
*/

#include <stdio.h>
#include <math.h>

#include <mpi.h>

#define N 840

int main(void)
{
    double pi;
    int i;

    /* MPI Variables */
    MPI_Status status;
    MPI_Comm comm;

    int rank, size, source, tag;

    /* Other Variables */
    int istart, istop;
    double partialpi, recvpi;

    printf("Computing approximation to pi using N = %d\n", N);

    /* Initialise MPI and compute number of processes and local rank */
    comm = MPI_COMM_WORLD;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    printf("Hello from rank %d \n", rank);

    /* Calculate partial pi value */
    partialpi = 0.0;
    istart = (rank * N / size) + 1;
    istop = ((rank + 1) * N) / size;

    for (i = istart; i <= istop; i++)
    {
        partialpi += 1.0 / (1.0 + pow(((double)i - 0.5) / (double)N, 2.0));
    }

    partialpi = (partialpi / (double)N) * 4.0;
    printf("pi = %.10f by rank %d \n", partialpi, rank);

    /* Compute global value of pi by sending partial values to rank 0 */

    if (rank == 0)
    {
        pi = partialpi; // initialise pi to locally computed pi

        for (source = 1; source < size; source++)
        {
            tag = 0;
            MPI_Recv(&recvpi, 1, MPI_DOUBLE, MPI_ANY_SOURCE, tag, comm, &status);
            printf("rank 0 receiving pi from rank %d \n", status.MPI_SOURCE);

            pi += recvpi;
        }
    }
    else
    {
        tag = 0;
        printf("rank %d sending pi to rank 0\n", rank);
        MPI_Ssend(&partialpi, 1, MPI_DOUBLE, 0, tag, comm);
    }

    if (rank == 0)
    {
        printf("final pi is %.10f  \n", pi);
    }

    MPI_Finalize();

    return 0;
}
