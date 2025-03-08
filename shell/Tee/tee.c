#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;
    int *file_descriptors;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    // Step 1: Parse command-line arguments
    if (argc < 2) {
        // No filenames provided, print a message and exit
        write(STDOUT_FILENO, "Usage: tee <file1> [file2] ...\n", 30);
        return 1;
    }

    // Allocate space for file descriptors for each file
    file_descriptors = malloc((argc - 1) * sizeof(int));
    if (file_descriptors == NULL) {
        perror("malloc");
        return 1;
    }

    // Step 2: Open each file for writing
    for (i = 1; i < argc; i++) {
        file_descriptors[i - 1] = open(argv[i], O_WRONLY | O_CREAT | O_TRUNC, 0644); // Open for writing
        if (file_descriptors[i - 1] == -1) {
            perror("Error opening file");
            free(file_descriptors); // Don't forget to free memory if there's an error
            return 1;
        }
    }

    // Step 3: Read from standard input and write to standard output and files
    while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        // Write to standard output
        bytes_written = write(STDOUT_FILENO, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to STDOUT");
            free(file_descriptors);
            return 1;
        }

        // Write to each output file
        for (i = 0; i < argc - 1; i++) {
            bytes_written = write(file_descriptors[i], buffer, bytes_read);
            if (bytes_written != bytes_read) {
                perror("Error writing to file");
                free(file_descriptors);
                return 1;
            }
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from STDIN");
    }

    // Step 4: Close the file descriptors
    for (i = 0; i < argc - 1; i++) {
        close(file_descriptors[i]);
    }

    // Free allocated memory
    free(file_descriptors);

    return 0;
}
