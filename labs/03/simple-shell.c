/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 80 /* 80 chars per line, per command */
#define STDIN 0
#define STDOUT 1

typedef int Process;
typedef char* String;

String* split(String str, char separator);

int main(void) {
	char args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 characters */
    int should_run = 1;
    const char sh[] = "osh> ";
    String* splitted;
    //String arg[] = {"ls", "-la", NULL};

    //read(STDIN, args, MAX_LINE/2 + 1);	
	//int i, upper;
    while (should_run){   
        //printf("osh>\n");
        //fflush(stdout);
        write(STDOUT, sh, sizeof(sh));
        /*
         * After reading user input, the steps are:
         * (1) fork a child process
         * (2) the child process will invoke execvp()
         * (3) if command included &, parent will invoke wait()
         */
        read(STDIN, args, MAX_LINE/2 + 1);
        if (strcmp(args, "exit\n") == 0) break;
        Process pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Error forking, errno = %d\n", errno);
            return 1;
        } else if (pid == 0) { //Child process
            //printf("forked child %s\n", args);
            splitted = split(args, ' ');
            printf("%d\n", execvp(splitted[0], splitted));
            free(splitted);
        } else { //Parent process
            //printf("waiting\n");
            wait(NULL);
            //printf("waited\n");
        }
    }
    //fork();
    //printf("%s has %d characters\n", arg[0], strlen(arg[0]));
   // printf("%d\n", execvp(arg[0], arg));
	return 0;
}

String* split(String str, char separator) {
    int spaces = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == separator) spaces++;
    }
    int index = 0;
    String* array = (String*) calloc(spaces + 2, sizeof(String));
    for (int i = 0; i < spaces + 2; i++) {
        array[i] = (String) calloc(32, sizeof(char));
    }
    String word = (String) calloc(32, sizeof(char));
    for (int i = 0; i < strlen(str); i++) {
        //printf("%c\n", str[i]);
        if (str[i] == '\n') break;
        if (str[i] == separator) {
            //array = realloc(array, (++index) * sizeof(String));
            strcpy(array[index++], word);
            //printf("%s\n", word);
            free(word);
            word = (String) calloc(32, sizeof(char));
        } else {
            String c = malloc(sizeof(char));
            *c = str[i];
            strcat(word, c);
            free(c);
        }
    }
    strcpy(array[index++], word);
    array[index] = NULL;
    free(word);
    return array;
}
