//Diego Ivan Morales Gallardo A01643382
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100
#define MAX_PATH_LENGTH 100

int main() {
    char user_input[MAX_INPUT_LENGTH];
    while (1) {
        printf("osh> ");
        fgets(user_input, sizeof(user_input), stdin);

        // remove trailing newline
        user_input[strcspn(user_input, "\n")] = '\0'; 

        pid_t pid = fork();
        if (pid == 0) { // Child process
            if (strcmp(user_input, "ls") == 0) {
                execlp("ls", "ls", NULL);
            } else if (strcmp(user_input, "pwd") == 0) {
                execlp("pwd", "pwd", NULL);
            } else if (strncmp(user_input, "cat", 3) == 0) {
                char *filename = strstr(user_input, " ");
                if (filename != NULL) {
                    filename++;  // Move past the space
                    execlp("cat", "cat", filename, NULL);
                } else {
                    printf("Usage: cat <filename>\n");
                }
            } else if (strcmp(user_input, "exit") == 0) {
                exit(0); // Child exits
            } else {
                printf("Invalid command. Please try again.\n");
            }
            exit(0); // Ensure child exits after command
        } else if (pid > 0) { // Parent process
            wait(NULL); // Wait for child to finish
        } else { // fork failed
            perror("fork");
            exit(1);
        }
    }
    return 0;
}
