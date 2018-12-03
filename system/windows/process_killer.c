#include<stdio.h>
#include<windows.h>

int main()
{
    /**
        define the variable UINT : unsigned integer : windows.h macro
        input the process id from user
    */
    UINT id;
    fprintf(stdout, "process id: ");
    fscanf(stdin, "%ud", &id);

    /**
        HANDLE data type for unique identifiers OpenProcess(...) return the
        handle of that ID's process.
        TerminateProcess(process handle, exit code) will return true for success.
    */

    HANDLE process;
    process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, id);
    if(!TerminateProcess(process,1)){
        fprintf(stdout, "failed to killed\n");
        CloseHandle(process);
        return -1;
    }

    fprintf(stdout, "process killed\n");
    CloseHandle(process);
    return 0;

    return 0;
}
