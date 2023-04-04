#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexcess-initializers"
#ifdef __unix__

#define OS_Windows 0
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <time.h>
    #include "Structs.c"

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include "Structs.c"

#define DIV 1048576
#define WIDTH 7

#endif

char R_TYPE [][10] = {"add" , "sub" , "slt" , "or" , "nand"};
char I_TYPE [][10] = {"addi" , "ori" , "slti" , "lui" , "lw" , "sw" ,"beq" ,"jalr"};
char J_TYPE [][10] = {"halt" , "j"};




//functions
void show_welcome_message();
void show_in_animataion(char *);
struct CharArray read_assembly_file(char *);
int get_value(struct Map * , int , char *);
struct Map * set_labels(int *, struct CharArray);
boolean is_in_map(struct Map *lables, int n, char *key);
boolean is_in_R_TYPE(char *);
boolean is_in_I_TYPE(char *);
boolean is_in_J_TYPE(char *);


int main() {
    if(OS_Windows)
    {
        system("color 06");
        struct CharArray tmp =  read_assembly_file("file.txt");
//        printf("%s", tmp.strs[0]);
    }
    else
        printf("This is Linux");

    //show_welcome_message();
    //////////////////////////////////////////////////////////////////
    int numberOfLabels = 0;
    struct CharArray strs = read_assembly_file("file.txt");
    struct Map * tmp = set_labels(&numberOfLabels,strs);
    for(int i = 0 ; i < numberOfLabels;i++)
        printf("%s : %d\n" , tmp[i].lable , tmp[i].address);


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
    show_in_animataion("\n\n WELCOME TO Miniature ASSEMBLER SIMULATION!\n TO START YOU SHOULD USE THE COMMAND "
                       "BELLOW:\n ---> ASSEMBLY INPUT_FILE.AC OUTPUT_FILE.MC\n\n");
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
        if(!is_in_R_TYPE(tmp) && !is_in_I_TYPE(tmp) && !is_in_J_TYPE(tmp))
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


#pragma clang diagnostic pop