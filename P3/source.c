#include<stdio.h>
#include<string.h>

#define STR_SIZE 10
#define SYMTAB "symtab.dat"
#define OPTAB "optab.dat"



int tabSearch(char filepath[], char xKey[])
{
    int flag = 0;
    char key[STR_SIZE], value[STR_SIZE];
    FILE *fp;

    fp = fopen(filepath, "r");

    while (!feof(fp))
    {
        fscanf(fp, "%s %s", &key, &value);
        if (strcmp(key, xKey) == 0)
        {
            flag = 1;
            break;
        }
    }

    fclose(fp);
    return flag;
}


int main()
{
    FILE *fp_input, *fp_output, *fp_symtab;
    int locctr, start = 0;
    char label[STR_SIZE], mnemonic[STR_SIZE], operand[STR_SIZE];

    fp_input = fopen("input.dat", "r");
    fp_symtab = fopen("symtab.dat", "w");
    fp_output = fopen("output.dat", "w");

    fscanf(fp_input, "%s %s %s", &label, &mnemonic, &operand);

    if (strcmp(mnemonic, "START") == 0)
    {
        start = atoi(operand);
        fprintf(fp_output, "%12s%12s%12s\n", label, mnemonic, operand);
        fscanf(fp_input, "%s %s %s", &label, &mnemonic, &operand);
    }

    locctr = start;

    while (strcmp(mnemonic, "END") != 0)
    {
        fprintf(fp_output, "%12d%12s%12s%12s\n", locctr, label, mnemonic, operand);
        if (strcmp(label, "-") != 0)
        {
            if (tabSearch(SYMTAB, label) == 1)
            {
                printf("ERROR: Duplicate symbol\n");
            }
            else
            {
                fprintf(fp_symtab, "%s %d\n", label, locctr);
            }
        }

        if (tabSearch(OPTAB, mnemonic) == 1) 
            locctr += 3;
        else if (strcmp(mnemonic, "WORD") == 0)
            locctr += 3;
        else if (strcmp(mnemonic, "RESW") == 0)
            locctr += (3 * atoi(operand));
        else if (strcmp(mnemonic, "RESB") == 0)
            locctr += atoi(operand);
        else if (strcmp(mnemonic, "BYTE") == 0)
            locctr = (operand[0] == 'X') ? locctr + 1 : locctr + strlen(operand) - 2;
        else
            printf("ERROR: Invalid operation code");

        fscanf(fp_input, "%s %s %s", &label, &mnemonic, &operand);
    }

    fprintf(fp_output, "%12d%12s%12s%12s", locctr, label, mnemonic, operand);
    printf("PROGRAM LENGTH: %d\n", locctr - start);

    fclose(fp_output);
    fclose(fp_symtab);
    fclose(fp_input);

    return 0;
}