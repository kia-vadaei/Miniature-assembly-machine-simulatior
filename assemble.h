

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

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <math.h>

//#include "assemble.h"

#define DIV 1048576
#define WIDTH 7

#endif

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
    size_t instType; // 0 means r type, 1 means i type and 2 means j type
    size_t intInst;
    size_t opCode;
    char *mnemonic;
    char inst[9];
    int rs;
    int rt;
    int rd;
    int imm;
    int PC;
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

char R_TYPE [][10] = {"add" , "sub" , "slt" , "or" , "nand"};
char I_TYPE [][10] = {"addi" , "ori" , "slti" , "lui" , "lw" , "sw" ,"beq" ,"jalr"};
char J_TYPE [][10] = {"j" , "halt"};
