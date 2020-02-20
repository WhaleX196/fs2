// fs_console.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Header.h"


#include <sstream>
#include <string.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
using namespace std;

#pragma pack(push, 1)

typedef struct _BOOT_NTFS
{
    BYTE    jump[3];
    BYTE    name[8];
    UINT16  sec_size;
    UINT16  secs_cluster;
    BYTE    zeros_0[6];
    UINT16  media_desc;
    BYTE    zeros_1;
    UINT16  secs_track;
    UINT16  num_heads;
    BYTE    zeros_2[8];
    UINT32  defaultValue;
    UINT64  num_secs;
    UINT64  LCNofMFT;
    UINT64  LCNofMFTMirr;
    DWORD  clustersPerMFT;
    UINT32  clustersPerIndex;
    UINT64  volumeSerialNumber;
} BOOT_NTFS;

#pragma pack(pop)

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

    char driveName;

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
    printf("\n\nSelected drive is: %c \n\n", driveName);


    string fileName = "\\\\.\\" + ((char)(driveName));
   fileName = fileName + ":";
   // wstring wide_string = wstring(narrow_string.begin(), narrow_string.end());
    //const wchar_t* result = wide_string.c_str();

    //const WCHAR* fileName = result;

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



    BOOT_NTFS* pBootRecord = reinterpret_cast<BOOT_NTFS*>(dataBuffer);

    cout << "File system type: " << pBootRecord->name << endl;
    cout << "Sector size: " << pBootRecord->sec_size << endl;
    cout << "Sectors per cluster: " << pBootRecord->secs_cluster << endl;
    cout << "Volume descriptor: " << pBootRecord->media_desc << endl;
    cout << "Sectors per track: " << pBootRecord->secs_track << endl;
    cout << "Number of heads: " << pBootRecord->num_heads << endl;
    cout << "Number of sectors: " << pBootRecord->num_secs << endl;
    cout << "First cluster of MFT: " << pBootRecord->LCNofMFT << endl;
    cout << "First cluster of MFT mirror: " << pBootRecord->LCNofMFTMirr << endl;
    cout << "Clusters per MFT Record: " << pBootRecord->clustersPerMFT << endl;
    cout << "Clusters per Index Record: " << pBootRecord->clustersPerIndex << endl;
    cout << "Volume serial number: " << pBootRecord->volumeSerialNumber << endl;

    CloseHandle(fileHandle);

    return 0;




}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
