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
        snprintf(message, sizeof(message), "Sending message from process %d of %d to process 0!", world_rank, world_size);

        // Print sending message info
        printf("Hi, I'm process %d of %d and I'm sending!\n", world_rank, world_size);

        // Send message to process 0
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);

        // Wait for response from process 0
        char response[100];
        MPI_Recv(response, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Print the response from process 0
        printf("Received response from process 0: %s\n", response);
    } else {
        printf("Hi, I'm process 0 of %d and I'm receiving!\n", world_size);

        // Process 0 receives the messages and sends a response
        for (int i = 1; i < world_size; i++) {
            char message[100];

            // Receive message from process i
            MPI_Recv(message, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            
            printf("%s\n", message);

            // Send response to process i
            char response[100];
            snprintf(response, sizeof(response), "Sending response from process 0 to process %d!", i);
            printf("Hi, I'm process 0 of %d and I'm sending a response to %d!\n", world_size, i);
            MPI_Send(response, strlen(response) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
