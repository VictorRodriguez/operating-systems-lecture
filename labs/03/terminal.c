// Alexei Delgado De Gante - A01637405
// Termnial program that can execute commands like pwd, ls, cat, etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

// Define constants for the maximum length of a command and path
#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 100

// Define a constant title
#define TERMINAL_TITLE "Iterminal5000"

// Function set_terminal_title() sets the title of the terminal from library <stdio.h>
void set_terminal_title(const char* title) {
    printf("\033]0;%s\007", title);
}

// Function print_initial_message() prints the initial message when the terminal is started
void print_initial_message() {
    printf("Welcome to %s\n", TERMINAL_TITLE);
    printf("Type 'info' for a list of available commands. Type 'exit' to terminate.\n");
}

// Function print_prompt() prints the prompt for the user to enter a command
void print_prompt() {
    // cwd as in current working directory
    char cwd[MAX_PATH_LENGTH];
    // getcwd() gets the current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        set_terminal_title(TERMINAL_TITLE);
        // Print the current working directory and the prompt
        printf("%s> ", TERMINAL_TITLE);
    // If getcwd() fails, print an error message and exit
    } else {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}

// Function execute_command() executes the command entered by the user
void execute_command(char* command) {
    // strtok() splits the command into tokens
    char* token = strtok(command, " ");
    // If the command is pwd, print the current working directory
    if (strcmp(token, "pwd") == 0) {
        char cwd[MAX_PATH_LENGTH];
        // getcwd() gets the current working directory
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        // If getcwd() fails, print an error message and exit
        } else {
            perror("getcwd() error");
            exit(EXIT_FAILURE);
        }
    // If the command is exit or quit, terminate the terminal
    } else if (strcmp(command, "exit") == 0 || strcmp(command, "quit") == 0) {
        printf("Exiting terminal.\n");
        exit(EXIT_SUCCESS);
    // If the command is info, print the list of available commands
    } else if (strcmp(command, "info") == 0) {
        printf("Available commands:\n");
        printf("1. info - Display available commands.\n");
        printf("2. exit or quit - Terminate the terminal.\n");
        printf("3. pwd - Print the current working directory.\n");
        printf("4. ls - List files and directories in the current directory.\n");
        printf("5. cat <filename> - Display the contents of a file.\n");
    // If the command is ls, list the files and directories in the current directory
    } else if (strcmp(token, "ls") == 0) {
        // opendir() opens the current directory, from library <dirent.h>
        DIR* dir;
        // readdir() reads the current directory, from library <dirent.h>
        struct dirent* entry;
        // If opendir() fails, print an error message and exit
        if ((dir = opendir(".")) != NULL) {
            // readdir() returns NULL when there are no more entries
            while ((entry = readdir(dir)) != NULL) {
                printf("%s\n", entry->d_name);
            }
            closedir(dir);
        // If opendir() fails, print an error message and exit
        } else {
            perror("opendir() error");
            exit(EXIT_FAILURE);
        }
    // If the command is cat, display the contents of a file
    } else if (strcmp(token, "cat") == 0) {
        token = strtok(NULL, " ");
        // If the command is cat without a filename, print an error message
        if (token == NULL) {
            printf("Usage: cat <filename>\n");
            return;
        }
        // fopen() opens a file, from library <stdio.h>
        FILE* file = fopen(token, "r");
        if (file == NULL) {
            perror("fopen() error");
            exit(EXIT_FAILURE);
        }
        // fgets() reads a line from a file, from library <stdio.h>
        char line[MAX_COMMAND_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Command not found: %s\n", token);
    }
}

// Function main() is the entry point of the program
int main() {
    // Define a char array for the command
    char command[MAX_COMMAND_LENGTH];
    print_initial_message();
    while (1) {
        // Print the prompt and get the command from the user
        print_prompt();
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0'; // remove trailing newline
        execute_command(command);
    }
    return 0;
}

