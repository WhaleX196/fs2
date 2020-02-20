// fs_console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Header.h"

#include <sstream>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>

using namespace std;

int main()
{
    std::cout << "Hello World!\n\n";

    
    if (Check_DLL())
    {
        printf("DLL here!\n\n");
    }
    else
    {
        printf("Huston, we have a problem!\n\n");
    }

    DWORD dr = GetLogicalDrives(); // функция возвращает битовую маску
    //printf("%d\n\n", dr);

    int n;

    string driveName;

    printf("Please, select one of the drives:\n\n");

    for (int x = 0; x < 26; x++) // проходимся циклом по битам
    {
        n = ((dr >> x) & 1); // узнаём значение текущего бита
        if (n) // если единица - диск с номером x есть
        {
           // std::string dl = (char)(65 + x); // получаем литеру диска
            std::string path = std::to_string(65 + x) + ":\\";

            //std::string out = "Диск " + dl + "\n";

            std::cout << "Disk: " << char(65 + x) << std::endl;
        }
    }

    driveName = cin.get();

    cout << "\n\n  Selected drive is:  " << driveName << "\n\n" << endl;

    string fileName = "\\\\.\\" + driveName + ":";

    HANDLE fileHandle = CreateFileA(
        fileName.c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (fileHandle == INVALID_HANDLE_VALUE)
    {
        perror("Error: ");
    }

    LARGE_INTEGER sectorOffset;
    sectorOffset.QuadPart = 0;

    unsigned long currentPosition = SetFilePointer(
        fileHandle,
        sectorOffset.LowPart,
        &sectorOffset.HighPart,
        FILE_BEGIN
    );

    if (currentPosition != sectorOffset.LowPart)
    {
        perror("Error: ");
    }

    BYTE dataBuffer[1024];

    DWORD bytesRead;

    bool readResult = ReadFile(
        fileHandle,
        dataBuffer,
        1024,
        &bytesRead,
        NULL
    );

    if (!readResult || bytesRead != 1024)
    {
        perror("Error: ");
    };
       
    BOOT_NTFS* BootRecord = reinterpret_cast<BOOT_NTFS*>(dataBuffer);

    //fs_info(fileName, BootRecord);

    Show_info(BootRecord);

    CloseHandle(fileHandle);

    return 0;
         
}

