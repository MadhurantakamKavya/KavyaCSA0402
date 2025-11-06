#include <stdio.h>
#include <windows.h>

int counter = 0;
CRITICAL_SECTION cs;

DWORD WINAPI threadFunction(LPVOID arg) {
    for (int i = 0; i < 1000000; ++i) {
        EnterCriticalSection(&cs);  // Lock
        counter++;
        LeaveCriticalSection(&cs);  // Unlock
    }
    return 0;
}

int main() {
    HANDLE thread1, thread2;

    // Initialize critical section (mutex equivalent)
    InitializeCriticalSection(&cs);

    // Create two threads
    thread1 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);
    thread2 = CreateThread(NULL, 0, threadFunction, NULL, 0, NULL);

    // Wait for threads to complete
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Clean up
    DeleteCriticalSection(&cs);
    CloseHandle(thread1);
    CloseHandle(thread2);

    printf("Final counter value: %d\n", counter);
    return 0;
}


