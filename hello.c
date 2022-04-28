#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        const char *msg = "Hello World\n";
        size_t s = strlen(msg) + 1; // Take care of the null char
        MPI_Send(&s, 1, MPI_UINT64_T, 1, 1, MPI_COMM_WORLD);
        printf("Message Sent\n");
        MPI_Send(msg, s, MPI_CHAR, 1, 1, MPI_COMM_WORLD);
    } else if (rank == 1) {
        size_t size;
        MPI_Recv(&size, 1, MPI_UINT64_T, 0, 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        char *msg = malloc(size * sizeof(char));
        MPI_Recv(msg, size, MPI_CHAR, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received Message: %s", msg);
        free(msg);
    }
    MPI_Finalize();
    return 0;
}