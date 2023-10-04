//Gian code implementation for calculating pi with monte carlo algorithm and threads
//A01638108 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

//first we define default points and threads
#define POINTS      100000 
#define num_threads     10

//work done per thread and thread array
int thread_work = POINTS/num_threads;
pthread_t Threads[num_threads];

//variables
double x,y;     //coordinates
int num_points = 0; //number of points
double d; //distance between two coordinated points
double pi; //final pi estimation
unsigned int Seed; //for random and time

//function to calculate the value of pi
void *calculatePi(void* argc){
    //randomly calculate the coordinates
    for(int  i=0; i<thread_work; i++){
        x=(double)rand_r(&Seed) / (double)((unsigned)RAND_MAX+1);
        y=(double)rand_r(&Seed) / (double)((unsigned)RAND_MAX+1);
        //calculate distance between points and add one to the num of points
        d=(x*x)+(y*y);
        if(d <= 1){
            num_points++;
        }
    }
}

int main(){

    //start clock and seed
    clock_t time_at_begin = clock();
    Seed = time(NULL);

     //create the threads
    for(int j=0; j<num_threads; j++){
        pthread_create(&Threads[j],NULL,calculatePi,NULL);
    }

    //manually "fork" all threads
    for(int i=0; i<num_threads; i++){
        pthread_join(Threads[i], NULL);
    }

    //estimate pi
    pi = (double)num_points/POINTS*4;

    // save the time required to get to this part of the code
    clock_t time_at_end = clock();
    double time_spent = (double)(time_at_end-time_at_begin) / CLOCKS_PER_SEC; 

    //display results
    printf("Time taken: %f\n",time_spent);

    printf("No. of points = %d , estimated pi is %g \n",POINTS,pi);

    return 0;
}