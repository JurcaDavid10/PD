#include <windows.h>
#include <winreg.h>
#include <stdio.h>

void iterateAllSubKeys(HKEY hKey)
{
    DWORD index = 0;
    TCHAR subKeyName[256]; 
    DWORD subKeyNameSize = 256;
    HKEY hSubKey;
    BYTE imagePath[1024]; 
    DWORD imagePathSize;
    DWORD retCode;

    while (RegEnumKeyEx(hKey, index, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        // Open each subkey
        if (RegOpenKeyEx(hKey, subKeyName, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
        {
            imagePathSize = sizeof(imagePath);
            // Query the "ImagePath" value
            if (RegQueryValueEx(hSubKey, TEXT("ImagePath"), NULL, NULL, imagePath, &imagePathSize) == ERROR_SUCCESS)
            {
                _tprintf(TEXT("Service: %s, ImagePath: %s\n"), subKeyName, (TCHAR*)imagePath);
            }
            else
            {
                _tprintf(TEXT("Service: %s, ImagePath: NOT FOUND\n"), subKeyName);
            }

            RegCloseKey(hSubKey);
        }

        subKeyNameSize = 256; // Reset size for next iteration
        index++;
    }
}

int main()
{
    HKEY hKey;
    // Open the "Services" registry key
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        printf("Opened registry key successfully.\n");
        iterateAllSubKeys(hKey);
        RegCloseKey(hKey);
    }
    else
    {
        printf("Failed to open registry key.\n");
    }

    return 0;
}
