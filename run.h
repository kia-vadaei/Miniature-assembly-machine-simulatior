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



struct RegisterFile
{
    int registers[16];
};
struct Memory
{
    int memory[65536];  //int is 4 bytes and 1 world
};



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



struct Memory memory;










int * decimal2binary(int number)
{
    // array to store binary number
    int binaryNum[32];

    for(int i = 0 ; i < 32 ; i++)
        binaryNum[i] = 0;

    int tmpNum = abs(number);

    // counter for binary array
    int i = 31;
    while (tmpNum > 0) {
        binaryNum[i] = tmpNum % 2;
        tmpNum = tmpNum / 2;
        i--;
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

struct Instruction * decode(struct Instruction *inst , struct RegisterFile * registerFile)    //returns the instruction
{
    if(inst->instType != 2) //not J_TYPE
    {
        if (inst->rd != -1)
            inst->rdVal = registerFile->registers[inst->rd];
        if (inst->rt != -1)
            inst->rtVal = registerFile->registers[inst->rt];
        if (inst->rs != -1)
            inst->rsVal = registerFile->registers[inst->rs];
    }

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
            return readData1 | readData2;
        case 4:     //nand
            *zero = 0;
            return !(readData1 & readData2);

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
            return readData2 | readData1;
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

struct Signals * ControlUnit(struct Instruction * inst)
{
    struct Signals * signals = malloc(sizeof (struct Signals));
    if(inst->instType == 0) // R-TYPE
        signals->RegDest = 1;
    else
        signals->RegDest = 0;

    if(inst->opCode == 13) //jump
        signals->Jump = 1;
    else
        signals->Jump = 0;

    if(inst->opCode == 11)
        signals->Branch = 1;
    else
        signals->Branch = 0;

    if(inst->opCode == 9) //lw
        signals->MemRead = 1;
    else
        signals->MemRead = 0;

    if(inst->opCode == 9) //lw
        signals->MemToReg = 1;
    else
        signals->MemToReg = 0;

    signals->ALUOp = inst->opCode;

    if(inst->opCode == 10) //sw
        signals->MemWrite = 1;
    else
        signals->MemWrite = 0;

    if(inst->instType == 0 || inst->opCode == 12 || inst->opCode == 11) //R-TYPE
        signals->ALUSrc = 0;
    else if(inst->instType == 1 && inst->opCode != 12) //I-TYPE and not jalr
        signals->ALUSrc = 1;

    if(inst->opCode != 10 && inst->opCode != 13 && inst->opCode != 14 && inst->opCode != 11)
        signals->RegWrite = 1;
    else
        signals->RegWrite = 0;

    if(inst->opCode == 12)
        signals->Jalr = 1;
    else
        signals->Jalr = 0;

    if(inst->opCode == 14)
        signals->Halt = 1;
    else
        signals->Halt = 0;

    if(inst->opCode == 8)
        signals->Upper = 1;
    else
        signals->Upper = 0;


    return  signals;
}

void memoryState(struct Instruction * inst , struct RegisterFile * registerFile , struct  Signals* signals , int * readDataFromMem , int ALUResult)
{
    if(signals->MemRead)
        *readDataFromMem = memory.memory[ALUResult];
    if(signals->MemWrite)
    {
        memory.memory[ALUResult] = inst->rtVal;
        *readDataFromMem = memory.memory[ALUResult];
    }
}

void writeBackState(struct RegisterFile * registerFile , struct  Signals* signals , int writeReg , int writeData)
{
    if(signals->RegWrite)
        registerFile->registers[writeReg] = writeData;
}


int execution(struct Instruction * inst , struct RegisterFile * registerFile)    //returns PC
{
    struct Signals * signals = ControlUnit(inst);   //generates the signals

    int tmpZero;
    int PC = ALU(0 , inst->PC , 1 , &tmpZero);   //PC+1

    PC = MUX_2_1(PC , -1 , signals->Halt);


    int writeReg = MUX_2_1(inst->rt , inst->rd, signals->RegDest);    //0 for rt and 1 for rd

    int readData1 = inst->rsVal;
    int readData2 = MUX_2_1(inst->rtVal , inst->imm , signals->ALUSrc);

    int zero = 0;
    int ALUResult = ALU(signals->ALUOp , readData1 , readData2 , &zero);


    int BranchSignal = zero & signals->Branch;


    int readDataFromMem = 0;



    memoryState( inst , registerFile ,signals , &readDataFromMem , ALUResult);

    int upperVal = inst->imm << 16;

    int instResult = MUX_3_2(ALUResult , upperVal , readDataFromMem , signals->MemToReg , signals->Upper);

    int writeData = MUX_2_1(instResult , PC , signals->Jalr);   //for jalr

    int branchTarget = ALU(0 , PC , inst->imm , &tmpZero);

    PC = MUX_2_1(PC , branchTarget , BranchSignal);

    PC = MUX_2_1(PC , inst->imm , signals->Jump); //for jump

    PC = MUX_2_1(PC , readData1 , signals->Jalr);


    writeBackState(registerFile , signals , writeReg , writeData);


    return PC;

}

