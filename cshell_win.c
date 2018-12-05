#include <stdio.h>
#include <string.h>
#include <windows.h>

#define _BUFFER 1024
#define _ERROR_LINE 0xC
#define _COMMAND_LINE 0xA

#define _ERROR -1
#define _NO_RETURN_ 0
#define HELP 1
#define PROCESS_LIST 2
#define APP_OPEN 3

const char delim[] = " -:";
char ntpd[] = "C:\\WINDOWS\\system32\\notepad.exe";

HANDLE color_handle;

void console_mode(WORD mode);
int tokenization(char *command);
void command_list();
BOOL compare(char *s1, char *s2);
BOOL processCreator(char *executer_path);
char* copy(char *s);
void killProcess(UINT id);

int main()
{
    color_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    console_mode(_COMMAND_LINE);
    fprintf(stdout,"C-Shell for Windows OS\n(c) 2018 Rafiul Islam\n\n");
    char command[_BUFFER];
    while(1)
    {
        fprintf(stdout, "[in] ");
        gets(command);
        switch(tokenization(command))
        {
            case _ERROR:{
                console_mode(_ERROR_LINE);
                fprintf(stderr, "[err] Invalid command\n");
                console_mode(_COMMAND_LINE);
            } break;
            case HELP: command_list(); break;
            case PROCESS_LIST: system("tasklist"); fprintf(stdout,"\n"); break;
            case APP_OPEN: fprintf(stdout, "[out] Notebook is opening\n"); break;
            case _NO_RETURN_: break;
        }
    }


    return 0;
}
void console_mode(WORD mode)
{
    SetConsoleTextAttribute(color_handle, mode);
}
void command_list()
{
    fprintf(stdout,"[out]\tTask\t\t\tCommand\n\t------------\t\t-------------\n");
    fprintf(stdout,"    \tProcess List\t\tpslist\n");
    fprintf(stdout,"    \tHelp\t\t\thelp\n");
    fprintf(stdout,"    \tOpen Notepad\t\tnotepad\n");
    fprintf(stdout,"    \tCreate Process\t\tps_create *location\n");
    fprintf(stdout,"    \tStop Process\t\tps_kill\n");
}
int tokenization(char *command)
{
    char temp[strlen(command)];
    strcpy(temp, command);
    char *tokens = strtok(temp, delim);

    if(compare("help", tokens))
    {
        tokens = strtok(NULL, delim);
        if(tokens != NULL)
        {
            return _ERROR;
        }
        return HELP;
    }
    if(compare("pslist", tokens))
    {
        tokens = strtok(NULL, delim);
        if(tokens != NULL)
        {
            return _ERROR;
        }
        return PROCESS_LIST;
    }
    if(compare("notepad", tokens))
    {
        tokens = strtok(NULL, delim);
        if(tokens != NULL)
        {
            return _ERROR;
        }
        if(processCreator(ntpd))
        {
            fprintf(stdout, "[out] notepad opened\n");
        }
        else
        {
            console_mode(_ERROR_LINE);
            fprintf(stderr, "[err] failed to create the process\n");
            console_mode(_COMMAND_LINE);
        }
        return _NO_RETURN_;
    }
    if(compare("echo", tokens))
    {
        int len = strlen(command);
        if(len > 5)
        {
            register int i;
            fprintf(stdout, "[out] ");
            for(i=5; i<len; i++)
                fprintf(stdout, "%c",command[i]);
            fprintf(stdout, "\n");
        }
        return _NO_RETURN_;
    }
    if(compare("ps_create", tokens))
    {
        tokens = strtok(NULL, delim);
        if(tokens != NULL)
        {
            return _ERROR;
        }
        fprintf(stdout,"[loc] ");
        char loc[_BUFFER];
        gets(loc);
        if(!processCreator(loc))
        {
            console_mode(_ERROR_LINE);
            fprintf(stderr, "[err] failed to create the process\n");
            console_mode(_COMMAND_LINE);
        }
        else
        {
            fprintf(stdout, "[out] process created\n");
        }
        return _NO_RETURN_;

    }
    if(compare("ps_kill", tokens))
    {
        tokens = strtok(NULL, delim);
        if(tokens != NULL)
        {
            return _ERROR;
        }
        fprintf(stdout,"[id] ");
        UINT id;
        fscanf(stdin, "%u", &id);
        killProcess(id);
        return _NO_RETURN_;
    }
    return -1;
}

BOOL compare(char *s1, char *s2)
{
    size_t s1_len = strlen(s1);
    size_t s2_len = strlen(s2);
    if(s1_len != s2_len) return FALSE;

    int i;
    for(i = 0; i<s1_len; i++)
    {
        if(s1[i] != s2[i])
            return FALSE;
    }

    return TRUE;
}
BOOL processCreator(char *executer_path)
{
    /**
        @see https://github.com/rafiulgits/HelloC/blob/master/system/windows/process_manage.c
    */
    STARTUPINFO si;
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));

    if(!CreateProcess(
                      NULL,/* use command line */
                      executer_path, /* location of the executor */
                      NULL, /* don't inherit process handle */
                      NULL, /* don't inherit thread handle */
                      FALSE, /* disable handle inheritance */
                      0, /* no creation flag */
                      NULL, /* use parent environment block */
                      NULL, /* use parent existing directory */
                      &si, /* startup information container */
                      &pi /* process information container */))
                      {
                          return FALSE;
                      }

    return TRUE;
}

void killProcess(UINT id)
{
    /**
        @see https://github.com/rafiulgits/HelloC/blob/master/system/windows/process_killer.c
    */
    HANDLE process;
    process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
    if(!TerminateProcess(process,1)){
        console_mode(_ERROR_LINE);
        fprintf(stderr, "[err] failed to kill the process\n");
        CloseHandle(process);
        console_mode(_COMMAND_LINE);
        return;
    }
    CloseHandle(process);
    fprintf(stdout, "[out] process killed\n");
    return;
}
