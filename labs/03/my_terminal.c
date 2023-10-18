#include <stdio.h> // printf, fgets
#include <stdlib.h> // exit, EXIT_FAILURE
#include <unistd.h> // fork, execlp
#include <string.h> // strcmp, strcspn
#include <sys/wait.h> // waitpid

//Maximum length of command
#define MAX_COMMAND_LENGTH 100


int main() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid; // Process ID
    int status; // Exit status

    printf("EXIT with: VEGA\n");
    while (1) {
        printf("VEGA_Terminal> ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove newline character from command
        command[strcspn(command, "\n")] = 0; // strcspn returns index of first occurence of newline character

        // Exit if user enters "VEGA"
        if (strcmp(command, "VEGA") == 0) { // strcmp returns 0 if strings are equal
            break;
        }

        pid = fork(); // Create child process

        if (pid == -1) { // fork returns -1 if error occurs
            perror("fork"); // Print error message
            exit(EXIT_FAILURE); // Exit with failure
        } else if (pid == 0) { // fork returns 0 if child process
            // Child process
            execlp(command, command, NULL); // Execute command in child process (execlp searches for command in PATH) (NULL is required as last argument)
            perror("execlp"); // Print error message
            exit(EXIT_FAILURE); // Exit with failure (if execlp returns, it failed)
        } else {
            // Parent process
            waitpid(pid, &status, 0); // Wait for child process to finish
        }
    }

    return 0;
}
