#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main() {
    HANDLE hMapFile;
    char* pBuf;
    const char* szName = "MySharedMemory";
    
    printf("Shared Memory Reader Process\n");
    printf("============================\n\n");
    
    // Open existing shared memory
    hMapFile = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        szName);
    
    if (hMapFile == NULL) {
        printf("OpenFileMapping failed: %d\n", GetLastError());
        printf("Make sure writer program is running first!\n");
        system("pause");
        return 1;
    }
    
    // Map to process
    pBuf = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 256);
    
    if (pBuf == NULL) {
        printf("MapViewOfFile failed: %d\n", GetLastError());
        CloseHandle(hMapFile);
        system("pause");
        return 1;
    }
    
    printf("Reading from shared memory...\n");
    printf("Message: %s\n\n", pBuf);
    
    // Cleanup
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    
    printf("Press any key to exit...");
    getchar();
    
    return 0;
}

