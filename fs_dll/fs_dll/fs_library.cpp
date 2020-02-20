#include "pch.h" 
#include <utility>
#include <limits.h>
#include <iostream>
#include <string.h>
#include <windows.h>
#include <stdio.h>

#include "Header.h"

int Check_DLL()
{
    return 1;
}

void Show_info(BOOT_NTFS* BootRecord)
{
    printf("File system type: %s \n\n", BootRecord->name);
    printf("Sector size: %d  \n\n", BootRecord->sec_size);
    printf("Sectors per cluster:  %d  \n\n", BootRecord->secs_cluster);
    printf("Volume descriptor: %d  \n\n", BootRecord->media_desc);
    printf("Sectors per track: %d \n\n", BootRecord->secs_track);
    printf("Number of heads: %d  \n\n", BootRecord->num_heads);
    printf("Number of sectors: %d \n\n", BootRecord->num_secs);
    printf("First cluster of MFT:  %d \n\n", BootRecord->LCNofMFT);
    printf("First cluster of MFT mirror: %d \n\n", BootRecord->LCNofMFTMirr);
    printf("Clusters per MFT Record: %d\n\n", BootRecord->clustersPerMFT);
    printf("Clusters per Index Record: %d\n\n", BootRecord->clustersPerIndex);
    printf("Volume serial number: %d\n\n", BootRecord->volumeSerialNumber);
}