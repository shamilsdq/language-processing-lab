#include <stdio.h>
#include <conio.h>
#include <string.h>


int main()
{
    int i, length = 0;
    int flag = 0;
    char id[32];

    printf("IDENTIFIER NAME: ");
    scanf("%s", &id);

    length = strlen(id);

    // CHECKS

    if (length <= 8) 
    {
        for (i = 0; i < length; ++ i)
        {
            if (((id[i] < 'A' || id[i] > 'Z') && (id[i] < 'a' || id[i] > 'z') && (id[i] != '_') && (id[i] < '0' || id[i] > '9')) || ((i == 0) && (id[i] >= '0' && id[i] <= '9')))
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0) 
        {
            printf("Valid\n");
            return 0;
        }
    }

    printf("Not valid\n");
    return 0;
}