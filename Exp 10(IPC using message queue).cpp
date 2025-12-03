#include <windows.h>
#include <stdio.h>
#include <string.h>
DWORD WINAPI receiverThread(LPVOID lpParam) {
    HANDLE hSlot;
    DWORD bytesRead;
    char buffer[256];
    hSlot = CreateMailslot(TEXT("\\\\.\\mailslot\\myqueue"),
                           0,
                           MAILSLOT_WAIT_FOREVER,
                           NULL);
    if (hSlot == INVALID_HANDLE_VALUE) {
        printf("Error creating message queue! %d\n", GetLastError());
        return 1;
    }
    printf("Receiver running... Waiting for messages...\n");
    while (1) {
        if (ReadFile(hSlot, buffer, sizeof(buffer), &bytesRead, NULL)) {
            buffer[bytesRead] = '\0';
            printf("\n[Received] %s\n", buffer);

            if (strcmp(buffer, "exit") == 0) {
                printf("Receiver exiting...\n");
                break;
            }
        }
    }
    CloseHandle(hSlot);
    return 0;
}
int main() {
    HANDLE hSender, hThread;
    DWORD bytesWritten;
    char message[100];
    hThread = CreateThread(NULL, 0, receiverThread, NULL, 0, NULL);
    Sleep(500); 
    hSender = CreateFile(TEXT("\\\\.\\mailslot\\myqueue"),
                         GENERIC_WRITE,
                         FILE_SHARE_READ,
                         NULL,
                         OPEN_EXISTING,
                         FILE_ATTRIBUTE_NORMAL,
                         NULL);
    if (hSender == INVALID_HANDLE_VALUE) {
        printf("Error opening message queue! %d\n", GetLastError());
        return 1;
    }

    printf("Sender ready.\n");
    printf("Type messages to send (type 'exit' to stop):\n");
    while (1) {
        printf("Enter message: ");
        scanf("%s", message);
        WriteFile(hSender, message, strlen(message), &bytesWritten, NULL);
        if (strcmp(message, "exit") == 0) {
            printf("Sender exiting...\n");
            break;
        }
    }
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hSender);
    return 0;
}

