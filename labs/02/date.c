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

void print_menu(){
    printf("Date binary to have fun\n");
    printf("-w : weeks of this year\n");
    printf("-d : days of this year \n");
    printf("-m : minutes of this year\n");
    printf("-s : seconds of this year\n");

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
    while ((option = getopt(argc, argv,"wdmsh")) != -1) {
        switch (option) {
            case 'w' :
                 seconds = get_time_seconds();
                 weeks = seconds / (7 * 24 * 60 * 60);
                 seconds % (7 * 24 * 60 * 60);
                 printf("Weeks in this year: %d\n",weeks);
                 if (seconds % (7 * 24 * 60 * 60) != 0 )
                     printf("We are running in week: %d \n",weeks+1);
                 else
                     printf("We are running in week: %d \n",weeks);
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
             case 'h' :
                 print_menu();
                 break;
             default: 
                 print_menu();
                 exit(-1);
            }
        }
    }else{
        get_date();
    }
}
