#ifdef __unix__

#define OS_Windows 0
#define boolean _Bool
#define Sleep sleep
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <time.h>
    #include <math.h>
    #include "Structs.c"
    #include <sys/types.h>
    #include <sys/stat.h>
//
//#include "run.c"
    #define clearConsole() printf("\033[H\033[J")

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#define clearConsole() system("cls")

#endif

//////////////////////////////////////////////////////////////////GLOBALS
#define _errors_address "Output/error.txt"
char globalInputFile[50];
boolean hasError;

///////////////////////////////////////////////////////////////////
struct CharArray
{
    char strs[500][255];
    int linesNum;
};

struct Map
{
    char lable[100];
    int address;
};

struct Instruction{
    size_t instType; // 0 means r type, 1 means i type and 2 means j type and 3 means dir type
    size_t intInst;
    size_t opCode;
    char inst[9];
    int rs;
    int rt;
    int rd;
    int rsVal;
    int rtVal;
    int rdVal;
    int imm;
    int target;
    int PC;
    int dir;
};

struct Error
{
    int line;
    int errorCode; // 0 is for the undefined label / 1 is for more than one use for a label / 2 is for offset overflow / 3 is for undefined opcode.
};

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
boolean is_op_code(char * );
int op_code_to_int(char * , int *);
char * decimal_to_hex(int);
int hex_to_decimal(char *);
char * reverse(char *);
void to_machine_code(struct Instruction * , int);

struct Instruction * set_each_line_inst(int  , struct Map* , struct CharArray );

void write_output(char * , int , struct Instruction * );
void write_error(char * , struct Error *);
char R_TYPE [][10] = {"add" , "sub" , "slt" , "or" , "nand"};
char I_TYPE [][10] = {"addi" , "slti" , "ori" , "lui" , "lw" , "sw" ,"beq" ,"jalr"};
char J_TYPE [][10] = {"j" , "halt"};
char DIR_TYPE[][10]  = {".fill" , ".space"};













