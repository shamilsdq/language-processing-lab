#include<stdio.h>
#include<conio.h>

#define INPUT_FILE "input.dat"


int main()
{
    int word_flag = 0;
    int count_c = 0, count_w = 0, count_l = 0;
    
    char ch;
    FILE *fp;

    fp = fopen(INPUT_FILE, "r");
    if (fp == NULL) 
    {
        printf("Error opening file - %s\n", INPUT_FILE);
        getch();
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF )
    {
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
        {
            if (word_flag)
            {
                word_flag = 0;
                ++ count_w;
            }
            if (ch == '\n') 
            {
                ++ count_l;
            }
        }
        else
        {
            ++ count_c;
            word_flag = 1;
        }
    }

    fclose(fp);

    printf("Characters = %d\n", count_c);
    printf("Words = %d\n", ++ count_w);
    printf("Lines = %d\n", ++ count_l);

    return 0;
}