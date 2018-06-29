#include <stdio.h>
#include <stdlib.h>

void secretFunction(int a , int b)
{
    printf("The answer is %d\n",a*b);
    exit(0);
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
