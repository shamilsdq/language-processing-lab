#include <stdio.h>



char input[50];
char container[20] = "";
int mode = 0, index = 0;


char keywords[30][15] = {
    "int", "char", "float", "if", "else", "switch", 
    "for", "while", "do", "break", "continue", "return"
};
char operators[30][5] = {
    "+", "-", "*", "/", "=", "&", "|", "^", "!", ">", "<", "?", ":",
    "++", "--", "+=", "-=", "*=", "/=", "<=", "!=", "==", ">=", "||", "&&",
};


int isDelimiter() 
{
    int i;
    char x = input[index];

    if (isOperator())
        return 1;

    if(x == ' ' || x == ',' || x == ';' || x == '(' || x == ')' || x == '[' || x == ']')
        return 1;

    return 0;
}

int isOperator()
{
    int i;
    for (i = 0; i < 13; ++i)
    {
        if (input[index] == operators[i][0])
            return 1;
    }
    return 0;
}





int isKeyword()
{
    int i;
    for (i = 0; i < 12; ++i)
    {
        if (strcmp(container, keywords[i]) == 0)
            return 1;
    }
    return 0;
}


int validateOperator()
{
    int i;
    for (i = 0; i < 17; ++i)
    {
        if (strcmp(container, operators[i]) == 0)
            return 1;
    }
    return 0;
}


int validateIdentifier()
{
    int i;
    if (container[0] < 65 && container[0] > 90 && container[0] < 97 && container[0] > 122 && container[0] != 95) 
        return 0;
    for (i = 1; i < strlen(container); ++i) 
    {
        if (container[0] < 65 && container[0] > 90 && container[0] < 97 && container[0] > 122 
            && container[0] < 48 && container[0] > 57 && container[0] != 95) 
            return 0;
    }
    return 1;
}


void processDFA() 
{
    while (index < strlen(input))
    {
        switch (mode) 
        {
            // fresh container
            case 0:
                if (input[index] >= 48 && input[index] <= 57)
                {
                    container[strlen(container) + 1] = 0;
                    container[strlen(container)] = input[index];
                    mode = 1;
                }
                else if ((input[index] >= 65 && input[index] <= 90) || (input[index] >=97 && input[index] <= 122) || input[index] == 95)
                {
                    container[strlen(container) + 1] = 0;
                    container[strlen(container)] = input[index];
                    mode = 2;
                }
                else if (input[index] == '(' || input[index] == ')' || input[index] == '[' || input[index] == ']' 
                        || input[index] == ' ' || input[index] == ',' || input[index] == ';' || input[index] == ':')
                {
                    mode = 0;
                }
                else if (isOperator())
                {
                    container[strlen(container) + 1] = 0;
                    container[strlen(container)] = input[index];
                    mode = 3;
                }
                else
                {
                    while(!isOperator())
                        index++;
                    container[strlen(container) + 1] = 0;
                    container[strlen(container)] = input[index];
                    mode = 3;
                }
                ++index;
                break;

            // number
            case 1:
                if (isDelimiter() || !(input[index] >= 48 && input[index] <= 57))
                {
                    printf("%20s : %s\n", "NUMBER", container);
                    memset(container, 0, sizeof container);
                    mode = 0;
                }
                else
                {
                    printf("%20s : %s\n", "NUMBER", container);
                    container[strlen(container) + 1] = 0;
                    container[strlen(container)] = input[index];
                    ++index;
                }
                break;

            // identifier or keyword
            case 2:
                if (isDelimiter())
                {
                    if (isKeyword())
                        printf("%20s : %s\n", "KEYWORD", container);
                    else 
                    {
                        if (validateIdentifier())
                            printf("%20s : %s\n", "VALID IDENTIFIER", container);
                    }
                    
                    memset(container, 0, sizeof container);
                    mode = 0;
                }
                else
                {
                    if (isKeyword())
                        printf("%20s : %s\n", "KEYWORD", container);
                    else 
                    {
                        if (validateIdentifier())
                            printf("%20s : %s\n", "VALID IDENTIFIER", container);
                        else
                           printf("%20s : %s\n", "INVALID IDENTIFIER", container); 
                    }
                    container[strlen(container) + 1] = 0;
                    container[strlen(container)] = input[index];
                    ++index;
                }
                break;

            // operator
            case 3:
                if (!isOperator() || strlen(container) == 2)
                {
                    if (validateOperator())
                        printf("%20s : %s\n", "OPERATOR", container);
                    memset(container, 0, sizeof container);
                    mode = 0;
                }
                else 
                {
                    if (validateOperator())
                        printf("%20s : %s\n", "OPERATOR", container);
                    container[strlen(container) + 1] = 0;
                    container[strlen(container)] = input[index];
                    ++index;
                }
                break;
        }
    }

    switch (mode) 
    {
        case 0:
            break;

        case 1:
            printf("%20s : %s\n", "NUMBER", container);
            break;

        case 2:
            if (isKeyword())
                printf("%20s : %s\n", "KEYWORD", container);
            else 
            {
                if (validateIdentifier())
                    printf("%20s : %s\n", "VALID IDENTIFIER", container);
                else
                   printf("%20s : %s\n", "INVALID IDENTIFIER", container); 
            }
            break;

        case 3:
            printf("%20s : %s\n", "OPERATOR", container);
            break;
    }
}


int main() 
{
    printf("Input line: ");
    gets(input);
    processDFA();
    return 0;
}