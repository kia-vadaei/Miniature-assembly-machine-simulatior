
#include "assemble.c"
#include "run.h"

int * decimal2binary(int number)
{
    // array to store binary number
    int binaryNum[32];

    for(int i = 0 ; i < 32 ; i++)
        binaryNum[i] = 0;

    int tmpNum = abs(number);

    // counter for binary array
    int i = 0;
    while (tmpNum > 0) {
        binaryNum[i] = tmpNum % 2;
        tmpNum = tmpNum / 2;
        i++;
    }
    if(number < 0)
    {
        boolean zeroIgnorFlag = 0;
        for(int i = 31 ; i >= 0 ; i--)
        {
            if(!binaryNum[i] && !zeroIgnorFlag)
                continue;
            else if(binaryNum[i] && !zeroIgnorFlag)
            {
                zeroIgnorFlag = 1;
                continue;
            }
            else if(zeroIgnorFlag)
                binaryNum[i] = !binaryNum[i];
        }
    }

    return binaryNum;

}

int binary2decimal(int * binaryNum)
{
    int decimal = 0;
    int base = 1;
    boolean isNegetiveFlag = 0;
    if(binaryNum[0])
    {
        isNegetiveFlag = 1;
        boolean zeroIgnorFlag = 0;
        for(int i = 31 ; i >= 0 ; i--)
        {
            if(!binaryNum[i] && !zeroIgnorFlag)
                continue;
            else if(binaryNum[i] && !zeroIgnorFlag)
            {
                zeroIgnorFlag = 1;
                continue;
            }
            else if(!binaryNum[i] && zeroIgnorFlag)
                binaryNum[i] = 1;
            else if(binaryNum[i] && zeroIgnorFlag)
                binaryNum[i] = 0;
        }
    }

    for (int i = 31 ; i >= 0 ; i--)
    {
        decimal += binaryNum[i] * base;
        base *= 2;
    }
    if(isNegetiveFlag)
        decimal *= -1;
    return decimal;
}


int MUX_2_1(int val0 , int val1 , int signal)
{
    if(!signal)
        return val0;
    return val1;
}
int MUX_3_2(int val0 , int val1 , int val2 , int signal1 , int signal2)
{
    if(!signal1 && !signal2)
        return val0;
    else if(!signal1 && signal2)
        return val1;
    else if(signal1 && !signal2)
        return val2;
}

struct Instruction *fetch(struct Instruction *insts, int pc)    //returns the instruction
{
    return insts + pc;
}

struct Instruction * decode(struct Instruction *inst)    //returns the instruction
{
    if(inst->rd != -1)
        inst->rdVal = memory.memory[inst->rd];
    if(inst->rt != -1)
        inst->rtVal = memory.memory[inst->rt];
    if(inst->rs != -1)
        inst->rsVal = memory.memory[inst->rs];

    //Note that all values in struct such as RValues and ImmValues are desimal

    return inst;
}

int ALU(int ALUOP , int readData1 , int readData2  , int * zero)   //*zero is a return value
{
    int * RD1;
    int * RD2;

    switch (ALUOP)
    {
        case 0:     //add
            *zero = 0;
            return readData1 + readData2;
        case 1:     //sub
            *zero = 0;
            return readData1 - readData2;
        case 2:     //slt
            *zero = 0;
            if(readData1 - readData2 < 0)
                return 1;
            else
                return 0;
        case 3:     //or
            *zero = 0;
            RD1 = decimal2binary(readData1);
            RD2 = decimal2binary(readData2);

            for(int i = 0; i < 32; i++)
                RD1[i] = RD1[i] | RD2[i];
            return binary2decimal(RD1);
            case 4:     //nand
            *zero = 0;
            RD1 = decimal2binary(readData1);
            RD2 = decimal2binary(readData2);

            for(int i = 0; i < 32; i++)
                RD1[i] = !(RD1[i] & RD2[i]);
            return binary2decimal(RD1);

            break;
        case 5:     //addi
            *zero = 0;
            return readData1 + readData2;
        case 6:     //slti
            *zero = 0;
            if(readData1 - readData2 < 0)
                return 1;
            else
                return 0;
        case 7:     //ori
            *zero = 0;
            RD1 = decimal2binary(readData1);
            RD2 = decimal2binary(readData2);

            for(int i = 0; i < 32; i++)
                RD1[i] = RD1[i] | RD2[i];
            return binary2decimal(RD1);
        case 9:     //lw
            *zero = 0;
            return readData1 + readData2;
        case 10:    //sw
            *zero = 0;
            return readData1 + readData2;
        case 11:    //beq
            if(!(readData1 - readData2))
                *zero = 1;
            else
                *zero = 0;
            return 0;
        default:
            return 0;

    }
}