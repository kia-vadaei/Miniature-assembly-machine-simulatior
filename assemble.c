#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexcess-initializers"


#include "assemble.h"




int main() {
    if(OS_Windows)
    {
        system("color 06");
        struct CharArray tmp =  read_assembly_file("file.txt");
//        printf("%s", labelsMap.strs[0]);
    }
    else
        printf("This is Linux");

    show_welcome_message();
    //////////////////////////////////////////////////////////////////
    int numberOfLabels = 0;
    int numberOfLines;
    struct CharArray strs = read_assembly_file("file.txt");

    numberOfLines = strs.linesNum;

    struct Map * labelsMap = set_labels(&numberOfLabels, strs);
    for(int i = 0 ; i < numberOfLabels;i++)
        printf("%s : %d\n" , labelsMap[i].lable , labelsMap[i].address);

    struct Instruction * insts = set_each_line_inst(numberOfLabels , labelsMap , strs);
    printf("%d, %d, %d",insts[6].imm , insts[6].rs , insts[6].rt);


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
    show_in_animataion("\n\n\t\t\t\t\tWELCOME TO Miniature ASSEMBLER SIMULATION!\n\t\t\t\t\tTO START YOU SHOULD USE THE COMMAND "
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
            printf("ERROR");
            return NULL;
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
        if (i == 5);

        while(!is_op_code(tmp))
            tmp = strtok(NULL, "\t");

        int tmpType; // to recognize the type of instruction
        insts[i].opCode = op_code_to_int(tmp , &tmpType); // to save opcode in decimal
        insts[i].instType = tmpType;
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
                        printf("ERROR");
                        exit(1);
                    }
                    break;
                case 1: // I_TYPE
                    insts[i].rt = strtol(rgstrs, &tmpEnd, 10); //rt
                    rgstrs = strtok(NULL, ",");//next one

                    insts[i].rs = strtol(rgstrs, &tmpEnd, 10);//rs
                    rgstrs = strtok(NULL, ",");//next one

                    if (rgstrs[0] >= '0' && rgstrs[0] <= '9') // if its number
                        insts[i].imm = strtol(rgstrs, &tmpEnd, 10); // imm
                        //addi $2,$4,6
                    else // if its label
                    {
                        int tmpInt = get_value(labels, numberOfLabels, rgstrs); //imm
                        if (tmpInt != -1)
                            insts[i].imm = tmpInt;
                        else {
                            printf("ERROR");
                            exit(1);
                        }
                    }
                    if(insts[i].rs > 15 || insts[i].rt > 15)
                    {
                        printf("ERROR");
                        exit(1);
                    }
                    break;
                case 2:
                    if (rgstrs[0] >= '0' && rgstrs[0] <= '9') // if its number
                        insts[i].imm = strtol(rgstrs, &tmpEnd, 10); // imm

                    else // if its label
                    {
                        int tmpInt = get_value(labels, numberOfLabels, rgstrs); //imm
                        if (tmpInt != -1)
                            insts[i].imm = tmpInt;
                        else {
                            printf("ERROR");
                            exit(1);
                        }
                    }
                    break;
                default:
                    printf("Error");
                    exit(1);
                    break;

            }
        }
        else // if it was halt
        {
            insts[i].opCode = 14;

        }
        insts[i].PC = i;


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










#pragma clang diagnostic pop