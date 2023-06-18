#ifndef MINIATURE_ASSEMBLY_MACHINE_SIMULATIOR_RUN_H
#define MINIATURE_ASSEMBLY_MACHINE_SIMULATIOR_RUN_H
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

struct RegisterFile
{
    int registers[16];
};

static struct RegisterFile registerFile = {
{0,30,45,7,88,6,70,68,54,10,11,36,20,90,100}
};



#endif //MINIATURE_ASSEMBLY_MACHINE_SIMULATIOR_RUN_H
