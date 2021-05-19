#include<stdio.h>
#include<conio.h>


/*
GRAMMER:
    E -> 2E2
    E -> 3E3
    E -> 4
*/


int mode = 0;
char stack[20] = "", input[20] = ""; 


void shift() 
{
    int i;
    stack[strlen(stack)] = input[0];
    stack[strlen(stack)] = '\0';

    for (i = 0; i < strlen(input) - 1; ++i)
        input[i] = input[i + 1];
    input[i] = '\0';
}


void reduce()
{
    int i, k = strlen(stack);
    switch (mode) 
    {
        case 1:
            stack[k - 1] = 'E';
            break;
        
        case 2:
            stack[k - 3] = 'E';
            stack[k - 2] = stack[k - 1] = 0;
            break;
    }
}


void printrow()
{
    printf("%15s$ %15s$ ", stack, input);
    if (mode == 0)
        printf("%10s\n", "SHIFT");
    else
        printf("%10s\n", "REDUCE");
}


void process()
{
    int k = 0;

    switch (mode) 
    {
        case 0:
            shift();
            printrow();
            break;
        
        default:
            reduce();
            printrow();
            mode = 0;
            break;
    }

    // check if mode should be made to non-zero (reduce)
    k = strlen(stack);

    if(k >= 3) 
    {
        if (stack[k - 1] == '2' && stack[k - 2] == 'E' && stack[k - 3] == '2')
            mode = 2;
        if (stack[k - 1] == '3' && stack[k - 2] == 'E' && stack[k - 3] == '3')
            mode = 2;
    }
    if (k > 0 && stack[k - 1] == '4') 
    {
        mode = 1;
    }
}


int main()
{
    printf("Grammer is:\n \tE -> 2E2\n \tE -> 3E3\n \tE -> 4\n");
    
    printf("\nEnter input string: ");
    gets(input);

    while (strlen(input) > 0)
    {
        process();
    }
    
    if (mode > 0) {
        reduce();
    }

    printrow();
    
    if (strlen(stack) == 1 && stack[0] == 'E') 
        printf("Accepted");
    else
        printf("Error");

    return 0;
}