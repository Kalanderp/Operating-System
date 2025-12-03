#include <stdio.h>
#include <windows.h>
int main(int argc, char *argv[]) {
    HANDLE hMap;
    char *shared_msg;
    if (argc == 2 && strcmp(argv[1], "child") == 0) {
        hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "MySharedMemory");
        if (hMap == NULL) {
            printf("Child: Error opening shared memory\n");
            return 1;
        }
        shared_msg = (char*) MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 1024);

        if (shared_msg == NULL) {
            printf("Child: Error mapping shared memory\n");
            return 1;
        }
        printf("Child: Reading from shared memory...\n");
        printf("Child: Message read: %s\n", shared_msg);
        UnmapViewOfFile(shared_msg);
        CloseHandle(hMap);
        return 0;  
    }
    hMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
                             0, 1024, "MySharedMemory");

    if (hMap == NULL) {
        printf("Parent: Error creating shared memory\n");
        return 1;
    }
    shared_msg = (char*) MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, 1024);
    if (shared_msg == NULL) {
        printf("Parent: Error attaching shared memory\n");
        return 1;
    }
    printf("Parent: Enter message to write: ");
    gets(shared_msg);
    printf("Parent: written to shared memory: %s\n", shared_msg);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    CreateProcess(NULL, "shared_memory_ipc.exe child", NULL, NULL, FALSE,
                   0, NULL, NULL, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);

    UnmapViewOfFile(shared_msg);
    CloseHandle(hMap);

    return 0;
}

