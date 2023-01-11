#include <stdio.h>
#include <mpi.h>

int main(void)
{
    // initialise MPI library, setting up internal DS
    MPI_Init(NULL, NULL);

    // print hello world
    printf("hello world\n");

    MPI_Finalize();
}