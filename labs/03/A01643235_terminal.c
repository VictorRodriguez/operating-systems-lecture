// Alfredo Romo Osorno
// A01643235
// IoT - Operating Systems
// Linux Terminal simulation project

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

// Global vars
#define SHELL_TEXT "superchell"

int main()
{
    while (1)
    {
        char USR_INPUT[1000];
        char *ARGV[11];  // Array to store a maximum of 10 Arguments (program name + 9 args) and a NULL termination char
        int ARGC = 0;

        //Tokenize text input and store each argument in ARGV[]
        printf("%s> ", SHELL_TEXT);
        if (fgets(USR_INPUT, sizeof(USR_INPUT), stdin) != NULL)
        {
            char *token = strtok(USR_INPUT, " \n");
            while (token != NULL)
            {
                ARGV[ARGC] = strdup(token);
                ARGC++;
                token = strtok(NULL, " \n");
            }

            //Check for exit
            if (ARGC > 0 && strcmp(ARGV[0], "exit") == 0)  
            {
                // Free allocated memory before exit
                for (int i = 0; i < ARGC; i++) {
                    free(ARGV[i]);
                }
                exit(0);
            }

            ARGV[ARGC] = NULL;  // Null-terminate the ARGV array

            pid_t PROCESS_ID; //Var to store the child process ID
            PROCESS_ID = fork();
            if (PROCESS_ID < 0)
            {
                //if an error is encountered, print error number
                fprintf(stderr, "Fork Failed | ERROR NUM: %d\n", errno);
                exit(-1);
            }

            //If the current code is running in the child process:
            if (PROCESS_ID == 0)
            {
                if (execvp(ARGV[0], ARGV) < 0)
                {
                    //If there's an error executing the foreign binary, inform the user
                    fprintf(stderr, "Execution failed for command: %s\n", ARGV[0]);
                    exit(-1);
                }
            }
            else
            {
                //If not in child, wait for child to finish execution
                int status;
                wait(&status);
            }

            // Free allocated memory after command execution
            for (int i = 0; i < ARGC; i++) {
                free(ARGV[i]);
            }
        }
    }

    return 0;
}
