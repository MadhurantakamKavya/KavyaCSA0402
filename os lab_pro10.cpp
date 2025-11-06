#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hPipe;
    char buffer[100];
    DWORD bytesWritten, bytesRead;

    // Create a named pipe
    hPipe = CreateNamedPipe(
        TEXT("\\\\.\\pipe\\MessagePipe"),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 1024, 1024, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Could not create named pipe (%lu)\n", GetLastError());
        return 0;
    }

    printf("Waiting for client to connect...\n");
    BOOL connected = ConnectNamedPipe(hPipe, NULL) ?
                     TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
    if (!connected) {
        printf("Client connection failed.\n");
        CloseHandle(hPipe);
        return 1;
    }

    // Write message to pipe
    strcpy(buffer, "Hello from server through named pipe!");
    WriteFile(hPipe, buffer, (DWORD)strlen(buffer) + 1, &bytesWritten, NULL);
    printf("Server sent: %s\n", buffer);

    // Read reply from client
    ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL);
    printf("Server received: %s\n", buffer);

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    return 0;
}

