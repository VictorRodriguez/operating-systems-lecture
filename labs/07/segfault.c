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
 * As can be clearly seen, in the first attempt, the code worked fine but in
 * the second attempt, a large command line argument probably overwrote the
 * return address stored on stack of the function func() and hence when the
 * control went back to this overwritten value any damn thing could have caused
 * a segmentation fault as this memory location mostly(until you are very
 * lucky) does not belong to our process. 
 * 
 * To debug : 
 *  https://www.cprogramming.com/debugging/valgrind.html
 *  https://gcc.gnu.org/bugs/segfault.html
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

