/*
 * =====================================================================================
 *
 *       Filename:  add.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/11/2018 05:28:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Victor Rodriguez (), vm.rod25@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "add.h"

int a[256] = {0}; 
int b[256] = {0};
int c[256] = {0};

void foo(){
        for (int i=0; i<256; i++){
            a[i] = b[i] + c[i];
        }
}

void fill_arrays(){
    for (int i=0; i<256; i++){
        b[i] = 1;
        c[i] = 2;

    }
}

int check_arrays(){
    int ret = 0;
    for (int i=0; i<256; i++){
        if (a[i] == 3)
            continue;
        else
            printf("FAIL, corruption in arithmetic");
            ret =  -1;
            break;
    }
    return ret;
}

void print_help(){
    printf("-h : Help\n");
    printf("-d <delay> : Delay in useconds\n");
}

int main(int argc, char **argv){

    clock_t t;
    double avg_time_taken;
    double time_taken;

    // initialize arrays
    fill_arrays();

    int delay_value = 0; // in useconds
    int index;
    int c;

    opterr = 0;
    while ((c = getopt (argc, argv, "hd:")) != -1)
    switch (c){
      case 'h':
        print_help();
        return 0;
      case 'd':
        delay_value = atoi(optarg);
        break;
      case '?':
        if (optopt == 'd')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return -1;
    }


    t = clock();
    for (int x=0; x<MAX; x++){
        foo();
        if (delay_value){
            usleep(delay_value);
        }
    }
    t = clock() - t;

    time_taken = ((double)t)/CLOCKS_PER_SEC;

    double delayin_sec = (double)delay_value / 1000000;
    avg_time_taken =(((double)t)/CLOCKS_PER_SEC) /MAX;

    // check aritmetic
    if (check_arrays())
        return -1;


    printf("Loops: %d\n",MAX);
    printf("Delay per function: %.9g in seconds \n",(delayin_sec));
    printf("Total time: %.9g seconds to execute \n",time_taken);
    printf("foo() took %.9g seconds in avg to execute \n", avg_time_taken );
    return 0;
}
