// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <iostream>
#include <string>
#include <vector>

#pragma comment(lib, "setupapi.lib")

int main() {
    HDEVINFO deviceInfoSet;
    SP_DEVINFO_DATA deviceInfoData;
    DWORD deviceIndex = 0;
    DWORD dataType;
    WCHAR deviceName[1024];
    DWORD bufferSize;

    // Obtine un set de informatii despre dispozitive pentru toate dispozitivele USB
    deviceInfoSet = SetupDiGetClassDevsA(
        nullptr,
        "USB",
        nullptr,
        DIGCF_ALLCLASSES | DIGCF_PRESENT
    );


    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Eroare la obtinerea informatiilor despre dispozitive." << std::endl;
        return 1;
    }

    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    std::wcout << L"Dispozitive USB conectate:\n" << std::endl;

    while (SetupDiEnumDeviceInfo(deviceInfoSet, deviceIndex, &deviceInfoData)) {
        bufferSize = 0;

        // Se obtine dimensiunea bufferului pentru numele dispozitivului
        SetupDiGetDeviceRegistryPropertyW(
            deviceInfoSet,
            &deviceInfoData,
            SPDRP_DEVICEDESC,
            &dataType,
            nullptr,
            0,
            &bufferSize
        );

        if (bufferSize > 0) {
            // Se obtine numele efectiv
            if (SetupDiGetDeviceRegistryPropertyW(
                deviceInfoSet,
                &deviceInfoData,
                SPDRP_DEVICEDESC,
                &dataType,
                reinterpret_cast<PBYTE>(deviceName),
                bufferSize,
                nullptr
            )) {
                std::wcout << L"- " << deviceName << std::endl;
            }
        }
        ++deviceIndex;
    }

    SetupDiDestroyDeviceInfoList(deviceInfoSet);
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
