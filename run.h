#ifndef MINIATURE_ASSEMBLY_MACHINE_SIMULATIOR_RUN_H
#define MINIATURE_ASSEMBLY_MACHINE_SIMULATIOR_RUN_H
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

struct RegisterFile
{
    int registers[16];
};
struct Memory
{
    int memory[65536];  //int is 4 bytes and 1 world
};

static struct RegisterFile registerFile = {
{0,30,45,7,88,6,70,68,54,10,11,36,20,90,100}
};

static  struct Memory memory;

struct Signals
{
    int RegDest;
    int Jump;
    int Branch;
    int MemRead;
    int MemToReg;
    int ALUOp;
    int MemWrite;
    int ALUSrc;
    int RegWrite;
    int Jalr;
    int Halt;
    int Upper;

};

#endif //MINIATURE_ASSEMBLY_MACHINE_SIMULATIOR_RUN_H
