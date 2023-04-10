#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexcess-initializers"
//#include <Mmsystem.h>


#include "assemble.h"


int main() {
    if(OS_Windows)
    {
        system("color 06");
//        printf("%s", labelsMap.strs[0]);
    }
    else
        printf("This is Linux");

    //show_welcome_message();
    //scanf("->%d");
    //////////////////////////////////////////////////////////////////
    mkdir("Output");
    mkdir("Input");
    int numberOfLabels = 0;
    int numberOfLines;
    struct CharArray strs = read_assembly_file("Input/file.txt");

    numberOfLines = strs.linesNum;

    struct Map * labelsMap = set_labels(&numberOfLabels, strs);
    for(int i = 0 ; i < numberOfLabels;i++)
        printf("%s : %d\n" , labelsMap[i].lable , labelsMap[i].address);

    struct Instruction * insts = set_each_line_inst(numberOfLabels , labelsMap , strs);


    to_machine_code(insts , numberOfLines);

    write_output(_output_address , numberOfLines , insts);

//    for(int i = 0 ; i < numberOfLines; i++)
//        printf("\n%s : %d\n" , insts[i].inst , (int) insts[i].intInst);

    //printf("%d, %d, %d",insts[6].opCode , insts[6].rs , insts[6].rt);

    //printf("\n%c\n" , decimal_to_hex(14)[0]);

    struct Error tmpErr = {-1,-1};
    write_error(_errors_address , &tmpErr);
    return 0;
}
void show_in_animataion(char * str)
{
    for(int i = 0 ; i < strlen(str) ; ++i)
    {
        printf("%c" , str[i]);
        Sleep(90);
    }
}

void show_welcome_message()
{
    show_in_animataion("\n\n\t\t\t\t\tWELCOME TO MINIATURE ASSEMBLER SIMULATION!\n\t\t\t\t\tTO START YOU SHOULD USE THE COMMAND "
                       "BELLOW:\n\t\t\t\t\t---> ASSEMBLY INPUT_FILE.AC OUTPUT_FILE.MC\n\n\t\t\t\t\t");
    Sleep(500);
}
struct CharArray read_assembly_file(char * fileName)
{
    struct CharArray rslt;

    // initializing FILE !!!
    FILE * filePtr;
    filePtr = fopen(fileName , "r");

    int i = 0; // array counter

    //to check if file does not exist!
    if (filePtr == NULL)
    {
        printf("file can't be opened \n");

        exit(1);
    }

    int bufferLength = 255;
    char buffer[bufferLength];

    while(fgets(buffer, bufferLength, filePtr)) {
        strcpy(rslt.strs[i] , buffer);
        i++;
    }
    rslt.linesNum = i;
    fclose(filePtr);
    return rslt;
}
int get_value(struct Map * lables , int n , char * key)
{
    if(key[strlen(key) - 1] == '\n')
        key[strlen(key) - 1] = '\0';
    for(int i = 0 ; i < n; i++)
    {
        if(!strcmp(lables[i].lable , key))
            return lables[i].address;
    }
    return -1;
}
boolean is_in_map(struct Map * lables , int n , char * key)
{
    for(int i = 0 ; i < n; i++)
    {
        if(!strcmp(lables[i].lable , key))
            return 1; //is_in_map
    }
    return 0;
}
struct Map * set_labels(int *n , struct CharArray rslt)
{
    struct Map * symbolTable = malloc(sizeof (struct Map) * 100);
    for(int i = 0 ; i < rslt.linesNum ;++i)
    {
        // Extract the first one
        char * tmp = strtok(rslt.strs[i], "\t");

        if(is_in_map(symbolTable , (*n) , tmp))
        {
            //label more than once
            struct Error err = {i + 1, 1};
            write_error(_errors_address , &err);
            exit(1);
        }
            //check that if the tmp string is not in any of r or i or j types
        if(!is_op_code(tmp))
        {
            strcpy(symbolTable[*n].lable , tmp); // to set the key(label)
            symbolTable[*n].address = i; //to set the line number (address)
            (*n)++;

        }
    }
    return symbolTable;

}

boolean is_in_R_TYPE(char * str)
{
    for(int i = 0 ; i < 5; i++)
    {
        char * s = R_TYPE[i];
        if (!strcmp(str, R_TYPE[i]))
            return 1;
    }
    return 0;
}
boolean is_in_I_TYPE(char * str)
{
    for(int i = 0 ; i < 8; i++)
        if(!strcmp(str , I_TYPE[i]))
            return 1;
    return 0;
}
boolean is_in_J_TYPE(char * str)
{
    for(int i = 0 ; i < 2; i++)
        if(!strcmp(str , J_TYPE[i]))
            return 1;
    return 0;
}
boolean is_op_code(char * str)
{
    if(!is_in_R_TYPE(str) && !is_in_I_TYPE(str) && !is_in_J_TYPE(str))
        return 0;
    return 1;
}

struct Instruction * set_each_line_inst(int numberOfLabels ,struct Map * labels, struct CharArray rslt)
{
    struct Instruction * insts = malloc(sizeof (struct Instruction) * 200);
    for(int i = 0 ; i < rslt.linesNum ; ++i)
    {
        char * tmp = strtok(rslt.strs[i], "\t");
        while(!is_op_code(tmp))
        {
            tmp = strtok(NULL, "\t");

            if(tmp == NULL)
            {
                struct Error err = {i+1 , 3};
                write_error(_errors_address , &err);
                exit(1);
            }
        }

        int tmpType; // to recognize the type of instruction
        insts[i].opCode = op_code_to_int(tmp , &tmpType); // to save opcode in decimal
        insts[i].instType = tmpType;
        insts[i].PC = i;
        if(strcmp(tmp , "halt") != 0) {
            tmp = strtok(NULL, "\t"); // go to field part

            char *rgstrs = strtok(tmp, ","); // to split by ","

            //reading fields
            char *tmpEnd;
            switch (insts[i].instType) {
                case 0: //R_TYPE
                    insts[i].rd = strtol(rgstrs, &tmpEnd, 10);
                    rgstrs = strtok(NULL, ",");//next one

                    insts[i].rs = strtol(rgstrs, &tmpEnd, 10);
                    rgstrs = strtok(NULL, ",");//next one

                    insts[i].rt = strtol(rgstrs, &tmpEnd, 10);

                    if(insts[i].rd > 15 || insts[i].rs > 15 || insts[i].rt > 15)
                    {
                        struct Error err = {i+1 , 4};
                        write_error(_errors_address , &err);
                        exit(1);
                    }
                    break;
                case 1: // I_TYPE
                    insts[i].rt = strtol(rgstrs, &tmpEnd, 10); //rt
                    rgstrs = strtok(NULL, ",");//next one

                    insts[i].rs = strtol(rgstrs, &tmpEnd, 10);//rs
                    rgstrs = strtok(NULL, ",");//next one

                    if (rgstrs[0] >= '0' && rgstrs[0] <= '9' || rgstrs[0] == '-') // if its number
                    {
                        insts[i].imm = strtol(rgstrs, &tmpEnd, 10); // imm
                        if(abs(insts[i].imm) > 65535)
                        {
                            struct Error err = {i+1 , 2};
                            write_error(_errors_address , &err);
                            exit(1);
                        }
                    }
                        //addi $2,$4,6
                    else // if its label
                    {
                        int tmpInt = get_value(labels, numberOfLabels, rgstrs); //imm
                        if (tmpInt != -1)
                            insts[i].imm = tmpInt;
                        else
                        {
                            struct Error err = {i+1 , 0};
                            write_error(_errors_address , &err);
                            exit(1);
                        }
                    }
                    if(insts[i].rs > 15 || insts[i].rt > 15)
                    {
                        struct Error err = {i+1 , 4};
                        write_error(_errors_address, &err);
                        exit(1);
                    }
                    break;
                case 2:
                    if (rgstrs[0] >= '0' && rgstrs[0] <= '9'|| rgstrs[0] == '-') // if its number
                        insts[i].imm = strtol(rgstrs, &tmpEnd, 10); // imm

                    else // if its label
                    {
                        int tmpInt = get_value(labels, numberOfLabels, rgstrs); //imm
                        if (tmpInt != -1)
                            insts[i].imm = tmpInt;
                        else {
                            struct Error err = {i+1 , 4};
                            write_error(_errors_address , &err);
                            exit(1);
                        }
                    }
                    break;
                default:
                    exit(1);
                    break;

            }
        }
        else // if it was halt
        {
            insts[i].opCode = 14;

        }


    }
    return insts;
}

int op_code_to_int(char * opCode , int * type)
{
    for(int i = 0 ; i < 5; ++i)
        if(!strcmp(opCode , R_TYPE[i]))
        {
            *type = 0;
            return i;
        }
    for(int i = 0 ; i < 8; ++i)
        if(!strcmp(opCode , I_TYPE[i]))
        {
            *type = 1;
            return i + 5;
        }
    for(int i = 0 ; i < 2; ++i)
        if(!strcmp(opCode , J_TYPE[i]))
        {
            *type = 2;
            return i + 13;
        }

}

char * decimal_to_hex(int decimalNumber)
{
    long int remainder, quotient;
    int i = 0, j, tmp;
    char * hexadecimalNumber = malloc(sizeof (char) * 100);
    quotient = decimalNumber;
    while (quotient != 0)
    {
        tmp = quotient % 16;
        //To convert integer into character
        if (tmp < 10)
            tmp = tmp + 48;
        else
            tmp = tmp + 55; // to convert to ABCDEF
        hexadecimalNumber[i++] = (char)tmp;
        quotient = quotient / 16;
    }
    if(i != 0)
        hexadecimalNumber[i] = '\0';
    else
    {
        hexadecimalNumber[i] = '0';
        hexadecimalNumber[i + 1] = '\0';
    }
    reverse(hexadecimalNumber);
    return hexadecimalNumber;
}

int hex_to_decimal(char * hexadecimalnumber)
{
    int decimalNumber = 0;
    // Storing hexa number digits in one array
    char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    int i, j, power = 0, digit;

    // Converting hexadecimal number to equivalent decimal
    // number
    for (i = (int)strlen(hexadecimalnumber) - 1; i >= 0; --i) {

        // search if given input character is present in the
        // array or not. if it present in the array then
        // find the equivalent decimal number for each hexa
        // digit
        for (j = 0; j < 16; j++)
            if (hexadecimalnumber[i] == hexDigits[j])
                decimalNumber += j * (int)pow(16, power);
        power++;
    }
    // printing the result

    return decimalNumber;
}

char * reverse(char * str)
{
    for(int i = 0 ; i < (int) strlen(str) / 2 ; i++)
    {
        char tmp = str[i];
        str[i] = str[strlen(str) - 1 - i];
        str[strlen(str) - 1 - i] = tmp;
    }
}

void to_machine_code(struct Instruction * inst , int numberOfLines)
{
    for(int i = 0 ; i < numberOfLines; ++i)
    {
        char * tmpImm;
        int tmpDif;
        switch (inst[i].instType)
        {
            case 0: //R_TYPE
                //Unused digits --->
                inst[i].inst[0] = '0';
                inst[i].inst[5] = '0';
                inst[i].inst[6] = '0';
                inst[i].inst[7] = '0';
                //////////////////////
                inst[i].inst[1] = decimal_to_hex(inst[i].opCode)[0];
                inst[i].inst[2] = decimal_to_hex(inst[i].rs)[0];
                inst[i].inst[3] = decimal_to_hex(inst[i].rt)[0];
                inst[i].inst[4] = decimal_to_hex(inst[i].rd)[0];
                break;
            case 1: //I_TYPE
                //Unused digits --->
                inst[i].inst[0] = '0';
                //////////////////////
                inst[i].inst[1] = decimal_to_hex(inst[i].opCode)[0];
                inst[i].inst[2] = decimal_to_hex(inst[i].rs)[0];
                inst[i].inst[3] = decimal_to_hex(inst[i].rt)[0];
                //////////////////////
                tmpImm = decimal_to_hex(inst[i].imm);

                tmpDif = 4 - (int)strlen(tmpImm);

                for(int j = 0 ; j  < tmpDif; j++)
                    inst[i].inst[j+4] = '0';

                for(int j = 0 ; j < 4 ; j++)
                    inst[i].inst[j+4+tmpDif] = tmpImm[j];

                break;
            case 2: //J_TYPE
                //Unused digits --->
                inst[i].inst[0] = '0';
                //////////////////////
                inst[i].inst[1] = decimal_to_hex(inst[i].opCode)[0];
                inst[i].inst[2] = '0';
                inst[i].inst[3] = '0';
                //////////////////////
                tmpImm = decimal_to_hex(inst[i].imm);

                tmpDif = 4 - (int)strlen(tmpImm);

                for(int j = 0 ; j  < tmpDif; j++)
                    inst[i].inst[j+4] = '0';

                for(int j = 0 ; j < 4 ; j++)
                    inst[i].inst[j+4+tmpDif] = tmpImm[j];

                break;
            default:
                //ERR
                break;
        }

        inst[i].intInst = hex_to_decimal(inst[i].inst);
    }
}

void write_output(char * fileName , int numberOfLines , struct Instruction * insts)
{
    FILE * filePtr;
    filePtr = fopen(fileName , "w");
    fprintf(filePtr , "");
    fclose(filePtr);

    filePtr = fopen(fileName , "a");

    //to check if file does not exist
    if (filePtr == NULL)
    {
        printf("file can't be opened \n");
        exit(1);
    }
    for(int i = 0 ; i < numberOfLines; i++)
        fprintf (filePtr ,"%d\n" , (int) insts[i].intInst);

    fclose(filePtr);
}

    void write_error(char * fileName , struct Error * err)
    {
        FILE * filePtr;
        filePtr = fopen(fileName , "w");

        int i = 0; // array counter

        //to check if file does not exist
        if (filePtr == NULL)
        {
            printf("file can't be opened \n");
            exit(1);
        }

        switch (err->errorCode)
        {
            case 0:
                fprintf(filePtr , "Process finished with exit code 1.\n\n--> Undefined label in line %d !" , err->line);
                break;
            case 1:
                fprintf(filePtr , "Process finished with exit code 1.\n\n--> The label defined in line %d has been defined more than once !" , err->line);
                break;
            case 2:
                fprintf(filePtr , "Process finished with exit code 1.\n\n--> The offset defined in line %d overflows the 16 bits !" , err->line);
                break;
            case 3:
                fprintf(filePtr , "Process finished with exit code 1.\n\n--> Undefined opcode in line %d !" , err->line);

                break;
            case 4:
                fprintf(filePtr , "Process finished with exit code 1.\n\n--> Wrong register called in line %d !" , err->line);
                break;
            default:
                fprintf(filePtr , "Process finished with exit code 0.");

                break;
        }
        fclose(filePtr);
    }

#pragma clang diagnostic pop






