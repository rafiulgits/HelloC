#include <stdio.h>
#include <string.h>
#include <windows.h>

#define _BUFFER 1024

#define _ERRORCONSOLE 1
#define _COMMANDCONSOLE 2

const char delim[] = " -:";

void console_mode(int mode);
int tokenization(char *command);
void command_list();

int main()
{
    console_mode(_COMMANDCONSOLE);
    fprintf(stdout,"C-Shell\n(c) 2018 Rafiul Islam\n\n");
    char command[_BUFFER];
    while(1)
    {
        fprintf(stdout, "[in] ");
        gets(command);
        switch(tokenization(command))
        {
            case 0: command_list(); break;
            case 1: system("tasklist"); fprintf(stdout,"\n"); break;
            default: continue; break;
        }
    }


    return 0;
}
void console_mode(int mode)
{
    switch(mode)
    {
        case _ERRORCONSOLE: system("color fc"); break;
        case _COMMANDCONSOLE: system("color fa"); break;
    }
}
void command_list()
{
    fprintf(stdout,"[out]\tTask\t\t\tCommand\n\t----\t\t\t--------\n");
    fprintf(stdout,"    \tProcess List\t\tpslist\n");
}
int tokenization(char *command)
{
    command = strlwr(command);
    if(strcmp(command, "help") == 0) return 0;
    if(strcmp(command, "pslist") == 0) return 1;
}
