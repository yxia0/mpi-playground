#include <stdio.h>
#include <mpi.h>

int main(void){
    
    int i;

    /* MPI variables */ 
    MPI_Comm comm;

    int rank, size;

    /* Other variables */
    int curr_val, sum_val, recv_val;
    int istop;

    /* Initialise MPI and get the size of the processors */
    comm = MPI_COMM_WORLD; 

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    printf("Hello from rank %d \n", rank);

    curr_val = rank;
    sum_val = 0;

    istop = size - 1;

    for (i = 1; i <= istop; i++){

        if (rank==0){
            // send msg
            MPI_Request request;
            printf("Process %d send value %d to its neighbour \n", rank, curr_val);
            MPI_Issend(&curr_val, 1, MPI_INT, 1, 0, comm, &request);
            // technically you can do things here, but lets assume an immediate send 
            MPI_Status status;
            MPI_Wait(&request, &status);
            // // receive msg from neighbour 
            // MPI_Recv(&recv_val, 1, MPI_INT, 3, 0, comm, MPI_STATUS_IGNORE);
            // printf("Process %d received value: %d.\n", rank, recv_val);
            // // update sum and curr_val 
            // sum_val += recv_val;
            // curr_val = recv_val;
        } else if (rank==1) {
            // send msg
            MPI_Request request;
            printf("Process %d send value %d to its neighbour \n", rank, curr_val);
            MPI_Issend(&curr_val, 1, MPI_INT, 2, 0, comm, &request);
            // technically you can do things here, but lets assume an immediate send 
            MPI_Status status;
            MPI_Wait(&request, &status);
            // // receive msg from neighbour 
            // MPI_Recv(&recv_val, 1, MPI_INT, 0, 0, comm, MPI_STATUS_IGNORE);
            // printf("Process %d received value: %d.\n", rank, recv_val);
            // // update sum and curr_val 
            // sum_val += recv_val;
            // curr_val = recv_val;
        } else if (rank==2) {
            MPI_Request request;
            printf("Process %d send value %d to its neighbour \n", rank, curr_val);
            MPI_Issend(&curr_val, 1, MPI_INT, 3, 0, comm, &request);
            // technically you can do things here, but lets assume an immediate send 
            MPI_Status status;
            MPI_Wait(&request, &status);
            // // receive msg from neighbour 
            // MPI_Recv(&recv_val, 1, MPI_INT, 1, 0, comm, MPI_STATUS_IGNORE);
            // printf("Process %d received value: %d.\n", rank, recv_val);
            // // update sum and curr_val 
            // sum_val += recv_val;
            // curr_val = recv_val;
        } else if (rank==3) {
            MPI_Request request;
            printf("Process %d send value %d to its neighbour \n", rank, curr_val);
            MPI_Issend(&curr_val, 1, MPI_INT, 0, 0, comm, &request);
            // technically you can do things here, but lets assume an immediate send 
            MPI_Status status;
            MPI_Wait(&request, &status);
            // // receive msg from neighbour 
            // MPI_Recv(&recv_val, 1, MPI_INT, 2, 0, comm, MPI_STATUS_IGNORE);
            // printf("Process %d received value: %d.\n", rank, recv_val);
            // // update sum and curr_val 
            // sum_val += recv_val;
            // curr_val = recv_val;
        }

        if (rank==0){
            // MPI_Status status;
            // MPI_Wait(&request, &status);
            // receive msg from neighbour 
            MPI_Recv(&recv_val, 1, MPI_INT, 3, 0, comm, MPI_STATUS_IGNORE);
            printf("Process %d received value: %d.\n", rank, recv_val);
            // update sum and curr_val 
            sum_val += recv_val;
            curr_val = recv_val; 
        } else if (rank==1) {
            // MPI_Status status;
            // MPI_Wait(&request, &status);
            // receive msg from neighbour 
            MPI_Recv(&recv_val, 1, MPI_INT, 0, 0, comm, MPI_STATUS_IGNORE);
            printf("Process %d received value: %d.\n", rank, recv_val);
            // update sum and curr_val 
            sum_val += recv_val;
            curr_val = recv_val;
        } else if (rank==2) {
            // MPI_Status status;
            // MPI_Wait(&request, &status);
            // receive msg from neighbour 
            MPI_Recv(&recv_val, 1, MPI_INT, 1, 0, comm, MPI_STATUS_IGNORE);
            printf("Process %d received value: %d.\n", rank, recv_val);
            // update sum and curr_val 
            sum_val += recv_val;
            curr_val = recv_val;
        } else if (rank==3) {
            // MPI_Status status;
            // MPI_Wait(&request, &status);
            // receive msg from neighbour 
            MPI_Recv(&recv_val, 1, MPI_INT, 2, 0, comm, MPI_STATUS_IGNORE);
            printf("Process %d received value: %d.\n", rank, recv_val);
            // update sum and curr_val 
            sum_val += recv_val;
            curr_val = recv_val;
        }
    }

    
    printf("final sum is %d om processor %d \n", sum_val, rank);

    MPI_Finalize();

    return 0;
}