#include <stdio.h>
#include <mpi.h>

/*
Output
Hello: rank 0, size of world: 4
Hello: rank 1, size of world: 4
Hello: rank 2, size of world: 4
Hello: rank 3, size of world: 4
*/

int main(void)
{
    MPI_Init(NULL, NULL);
    int rank;
    int world;
    // Get rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Get number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &world);
    printf("Hello: rank %d, size of world: %d\n", rank, world);
    MPI_Finalize();
}