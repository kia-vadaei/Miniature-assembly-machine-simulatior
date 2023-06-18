#include "stdio.h"
#include "stdlib.h"
#include "assemble.c"

int random(int n)
{
    srand(time(0));
    return rand() % n;
}

struct Instruction *fetch(struct Instruction *insts, int pc)
{

    return insts + pc;
}

