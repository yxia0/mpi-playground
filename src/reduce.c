#include <stdio.h>
#include <mpi.h>

int main(void) {


    int val;
    // MPI variables 
    int rank, size; 
    MPI_Comm comm;

    // Other variables 
    int root_rank = 0;
    int reduction_result =0; // init as 0

    // initialise MPI process 
    MPI_Init(NULL, NULL);

    comm = MPI_COMM_WORLD; 
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size); 

    val = rank;

    MPI_Reduce(&val, &reduction_result, 1, MPI_INT, MPI_SUM, root_rank, comm);

    if (rank == 0) {
        printf("The global sum is %d \n", reduction_result);
    }

    MPI_Finalize();
}