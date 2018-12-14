#include <stdio.h>
/*
 * IMPORTANT: To compile 32 bit binaries on 64 bit Linux version, you have to
 * Install libx32gcc development package and 32 bit GNU C Library
 */

void secretFunction()
{
    printf("Congratulations!\n");
    printf("You have entered in the secret function!\n");
}

void echo()
{
    char buffer[20];

    printf("Enter some text:\n");
    scanf("%s", buffer);
    printf("You entered: %s\n", buffer);    
}

int main()
{
    echo();

    return 0;
}
