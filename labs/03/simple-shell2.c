#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* Maximum characters per command line */
#define STDIN 0
#define STDOUT 1

const char* Tux =
    "    __      \n"
    " -=(o '.    \n"
    "    '.-.\\   \n"
    "    /|  \\\\  \n"
    "    '|  ||  \n"
    "     _\\_):,_" ;


void displayTux(){
    int lengthTux = strlen(Tux);

    for (int i = 0; i < lengthTux; i++) {
        if (Tux[i] == '\n') {
            write(STDOUT, "\n", 1); // Print a newline character
        } else {
            write(STDOUT, &Tux[i], 1); // Print the character
        }
    }
}

int main(void) {
    char args[MAX_LINE/2 + 1]; // Buffer for user input
    int should_run = 1; // Flag to control the shell loop

    while (should_run) {
        displayTux(); // Print Tux at the beginnign of each line
        printf(">>> "); // Prompt string

        // Read user input
        fgets(args, MAX_LINE/2 + 1, stdin); // Prevents buffer overflow, and read() does not

        // Check if the user wants to exit the shell
        if (strcmp(args, "exit\n") == 0) break;

        pid_t pid = fork(); // Create a child process
        if (pid < 0) {
            fprintf(stderr, "Error forking, errno = %d\n", errno);
            return 1;
        } else if (pid == 0) { // Child process
            args[strlen(args) - 1] = '\0'; // Remove the newline character at the end
            char* argv[MAX_LINE/2 + 1];
            char* token = strtok(args, " "); // Tokenize the input

            int i = 0;
            while (token != NULL) {
                argv[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            argv[i] = NULL;

            // Execute the command
            if (execvp(argv[0], argv) == -1) {
                perror("execvp"); // Print an error message if execvp fails
                exit(EXIT_FAILURE);
            }
        } else { // Parent process
            int status;
            wait(&status); // Wait for the child process to complete
        }
    }

    return 0;
}
