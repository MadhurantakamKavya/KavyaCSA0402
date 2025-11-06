#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    // Create a named shared memory mapping
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use paging file
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write access
        0,                       // Max. object size (high-order DWORD)
        1024,                    // Max. object size (low-order DWORD)
        TEXT("SharedMemoryExample")); // Name of mapping object

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // Map shared memory into address space
    pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,               // Handle to map object
        FILE_MAP_ALL_ACCESS,    // Read/write permission
        0,
        0,
        1024);

    if (pBuf == NULL) {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Write to shared memory
    CopyMemory((PVOID)pBuf, "Hello, shared memory!", 22);

    printf("Data written to shared memory: %s\n", pBuf);

    // Unmap and close
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}

