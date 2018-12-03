#include<stdio.h>
#include<windows.h>

int main()
{
    /**
        input an executable program location
        C:\WINDOWS\system32\notepad.exe
    */
    fprintf(stdout ,"Enter executable location: ");
    char loc[1000];
    gets(loc);

    /**
        STARTUPINFO structure contains information which is used to
        control how the process behaves and appears on startup.

        PROCESS_INFORMATION structure contains the created process
        and its thread and their ID.
    */
    STARTUPINFO si;
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;


    /**
        ZeroMemory function fills a block of memory with zeros. Used
        for memory allocation
    */
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));


    /**
        CreateProcess function used for request to create a new child
        process (root is OS); which return true for success and false for failed.
    */
    if(!CreateProcess(
                      NULL,/* use command line */
                      loc, /* location of the executor */
                      NULL, /* don't inherit process handle */
                      NULL, /* don't inherit thread handle */
                      FALSE, /* disable handle inheritance */
                      0, /* no creation flag */
                      NULL, /* use parent environment block */
                      NULL, /* use parent existing directory */
                      &si, /* startup information container */
                      &pi /* process information container */))
                      {
                          fprintf(stderr,"failed to create");
                          return -1;
                      }

    fprintf(stdout, "process created - ID: %d\n",pi.dwProcessId);

    // parent will wait for the child to complete
    WaitForSingleObject(pi.hProcess, INFINITE);

    //close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
