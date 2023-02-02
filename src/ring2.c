#include <stdio.h>
#include <mpi.h>

int main(void){
    
    int i;

    /* MPI variables */ 
    MPI_Comm comm;
    MPI_Request send_request;
    MPI_Status send_status;

    int rank, size;

    /* Other variables */
    int curr_val, sum_val, recv_val;
    int istop;
    int sendest, recvdest;

    /* Initialise MPI and get the size of the processors */
    comm = MPI_COMM_WORLD; 

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    double tstart, tstop;
    MPI_Barrier(MPI_COMM_WORLD);
    tstart = MPI_Wtime();

    printf("Hello from rank %d \n", rank);

    sendest = (rank+1) % size;
    recvdest = (rank-1) % size;
    curr_val = rank;
    sum_val = rank;

    istop = size - 1;

    for (i = 1; i <= istop; i++){
        
        printf("Step %d: Process %d send value %d to its neighbour \n", i, rank, curr_val);    
        MPI_Sendrecv(&curr_val, 1, MPI_INT, sendest, 0,
                 &recv_val, 1, MPI_INT, recvdest, 0, comm, MPI_STATUS_IGNORE);
        MPI_Barrier(MPI_COMM_WORLD);

        printf("Step %d: Process %d received value: %d.\n", i, rank, recv_val);
        // update sum and curr_val 
        printf("Step %d: Process %d is adding %d to sum %d \n", i, rank, recv_val, sum_val);
        sum_val += recv_val;
        curr_val = recv_val; 
        MPI_Barrier(MPI_COMM_WORLD);
        
    }       
    MPI_Barrier(MPI_COMM_WORLD);    

    printf("final sum is %d on processor %d \n", sum_val, rank);
    tstop = MPI_Wtime();
    double time = tstop - tstart;
    printf("Processor %d takes %f seconds \n", rank, time);

    MPI_Finalize();

    return 0;
}