#include <windows.h>
#include <stdio.h>

static const char* filename = ".\\test_file.txt";

int main()
{
    /*
    FILETIME ftCreate, ftAccess, ftWrite;

    // Get a handle to our file and with file_write_attributes access
    HANDLE fileHandle = CreateFile(filename, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // Get the file time on the file
    GetFileTime(fileHandle, &ftCreate, &ftAccess, &ftWrite);

    // Writing to the file
    FILE* filePtr = fopen(filename, "w");
    fprintf(filePtr, "%s", "hello world");
    fclose(filePtr);

    // Set the file time on the file
    SetFileTime(fileHandle, &ftCreate, &ftAccess, &ftWrite);

    // Close our handle.
    CloseHandle(fileHandle);
    */
    // Create a systemtime struct
    SYSTEMTIME thesystemtime;

    // Get current system time and then change the day to the 3rd
    // You can also change year, month, day of week etc
    GetSystemTime(&thesystemtime);
    thesystemtime.wHour = 21;
    thesystemtime.wDay = 1;

    // Create a FILETIME struct and convert our new SYSTEMTIME
    // over to the FILETIME struct for use in SetFileTime below
    FILETIME thefiletime;
    SystemTimeToFileTime(&thesystemtime,&thefiletime);

    // Get a handle to our file and with file_write_attributes access
    HANDLE filename = CreateFile(filename, FILE_WRITE_ATTRIBUTES, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    // Set the file time on the file
    SetFileTime(filename,(LPFILETIME) &thefiletime,(LPFILETIME) &thefiletime,&thefiletime);

    // Close our handle.
    CloseHandle(filename);
    return 0;
}