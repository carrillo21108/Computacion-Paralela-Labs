// Brian Anthony Carrillo Monzon
// 21108

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Print off a hello world message
    printf("Hello World, I'm process %d of %d!\n", world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
