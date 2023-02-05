#include <stdio.h>
#include <mpi.h>

#define ITER_NUM 80000
#define MSG_LEN 1000000

int main(void){

    // MPI variables 
    int rank, size;
    MPI_Comm comm;

    // Other variables
    int recev[MSG_LEN];
    double tstart, tend, ttime;

    // initialise array 
    int msg[MSG_LEN];
    for (int i=0; i < MSG_LEN; i++){
        msg[i] = 5;
    }
    
    MPI_Init(NULL, NULL);

    comm = MPI_COMM_WORLD;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size); 

    if (size > 2) {
        printf("Warning: processors with rank higher than 2 will not be used!");
    }

    tstart = MPI_Wtime();

    for (int j=0; j<ITER_NUM; j++){
        if (rank == 0){
        MPI_Ssend(msg,MSG_LEN,MPI_INT,1,0,comm);
        // printf("rank 0 send message to rank 1 \n");
    } else if (rank == 1) {
        MPI_Recv(recev,MSG_LEN,MPI_INT,0,0,comm, MPI_STATUS_IGNORE);
        // printf("rank 1 received message from rank 0 \n");
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 1){
        MPI_Ssend(recev,MSG_LEN,MPI_INT,0,0,comm);
        // printf("rank 1 send back message to rank 0 \n");
    } else if (rank ==0) {
        MPI_Recv(msg,MSG_LEN,MPI_INT,1,0,comm, MPI_STATUS_IGNORE);
        // printf("rank 0 received back message from rank 1 \n");
    }
    }

    tend = MPI_Wtime();
    ttime = tend - tstart;
    printf("Time elapsed: %f \n", ttime);

    MPI_Finalize();


}