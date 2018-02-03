#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <getopt.h>


void get_date(){
	time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("Date: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon \
            + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int get_time_seconds(){
    
	time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int seconds;
    seconds = tm.tm_sec;
    seconds += tm.tm_min * 60;
    seconds += tm.tm_hour * 60 * 60;
    seconds += tm.tm_mday * 24 * 60 * 60;
    seconds += tm.tm_mon * 30 * 24 * 60 * 60;
    return seconds;
}
int main(int argc , char *argv[]){

	int weeks,days,minutes,seconds =0;
    int option = 0;

    if (argc != 1 ){
    while ((option = getopt(argc, argv,"wdms")) != -1) {
        switch (option) {
            case 'w' :
                 seconds = get_time_seconds();
                 weeks = seconds / (7 * 24 * 60 * 60);
                 printf("Weeks in this year: %d\n",weeks);
                 break;
             case 'd' :
                 seconds = get_time_seconds();
                 days = seconds / (24 * 60 * 60);
                 printf("Days in this year: %d\n",days);
                 break;
             case 'm' :
                 seconds = get_time_seconds();
                 minutes = seconds / (60);
                 printf("Minutes in this year: %d\n",minutes);
                 break;
             case 's' :
                 seconds = get_time_seconds();
                 printf("Seconds in this year: %d\n",seconds);
                 break;
             default: printf("Error");
                 exit(-1);
            }
        }
    }else{
        get_date();
    }
}
