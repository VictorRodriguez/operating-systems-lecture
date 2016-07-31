/* CPU burst time calculation 
 * 
 * Create a program that calculate the CPU Burst time of a given process
 * It should differentiate from CPU burst and I/O burst
 * 
 * */

#include<stdio.h>

int main()
{
    int count=0;
    while(count<10){
        count++;
        printf("%d\n",count);
    }
    printf("%d\n",count);
    return 0; 
}

