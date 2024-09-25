// Brian Anthony Carrillo Monzon
// 21108

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank != 0) {
        // Message to send to process 0
        char message[100];
        snprintf(message, sizeof(message), "Greetings process 0, I'm process %d of %d!", world_rank, world_size);

        // Print sending message info
        printf("Hi, I'm process %d of %d and I'm sending a message to 0!\n", world_rank, world_size);

        // Send message to process 0
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        // Process 0 receives the messages
        printf("Hi, I'm process 0 of %d and I'm receiving!\n", world_size);
        
        for (int i = 1; i < world_size; i++) {
            char message[100];

            // Receive message from process i
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Print received message
            printf("%s\n", message);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}
