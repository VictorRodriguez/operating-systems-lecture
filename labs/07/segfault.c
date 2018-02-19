 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
/*
 * https://www.go4expert.com/articles/reasons-segmentation-fault-c-t27220/
 *
 * In this code, we are passing the command line argument array to
 * function func(). Inside the function func(), we try to copy the second
 * command line argument (with index '1') into the array arr. The problem here
 * is the function we use to copy. We use strcpy() which has no concern with
 * the capacity of array arr. This function will not detect or prevent a buffer
 * overflow. So if we try to enter very huge string through this logic
 * presented above, we will definitely overwrite the return address kept in the
 * stack of this function and will cause a segmentation fault to happen. 
 *
 *
 */

 void func(char ** argv)
 {
     char arr[2];
     strcpy(arr, argv[1]);

     return;
 }

 int main(int argc, char *argv[])
 {
     func(argv);
     return 0;
 }

