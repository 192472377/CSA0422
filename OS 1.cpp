#include <stdio.h>
#include <windows.h>

int main() {
    DWORD pid = GetCurrentProcessId();
    
    printf("Current Process ID: %lu\n", pid);
    printf("Note: Getting parent PID requires additional Windows API calls\n");
    
    system("pause");
    return 0;
}
