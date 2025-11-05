#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int source_fd, dest_fd;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    // Open source file for reading
    source_fd = open("source.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        exit(1);
    }

    // Open destination file for writing (create/truncate)
    dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening destination file");
        close(source_fd);
        exit(1);
    }

    // Copy contents from source to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (bytes_read < 0)
        perror("Error reading from source file");

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully using system calls!\n");
    return 0;
}

