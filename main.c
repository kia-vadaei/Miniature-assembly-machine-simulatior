#ifdef __unix__

#define OS_Windows 0
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>

#elif defined(_WIN32) || defined(WIN32)

#define OS_Windows 1
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#define DIV 1048576
#define WIDTH 7

#endif

struct CharArray
{
    char strs[500][255];
};


struct CharArray read_assembly_file(char *);
int main() {
    if(OS_Windows)
    {
        system("color 06");
//        struct CharArray tmp =  read_assembly_file("file.txt");
//        printf("%s", tmp.strs[0]);
    }
    else
        printf("This is Linux");

    //////////////////////////////////////////////////////////////////





    return 0;
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
    return rslt;
}