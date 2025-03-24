// Lab2Bonus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <iostream>

int main() {
    // 1. Aflam dimensiunea unei pagini
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD pageSize = si.dwPageSize;

    std::cout << "Dimensiunea unei pagini este: "
        << pageSize << " bytes.\n\n";

    // 2. Citim numarul N de pagini
    std::cout << "Introduceti un numar N (numarul de pagini de alocat): ";
    int N;
    std::cin >> N;

    if (!std::cin || N <= 0) {
        std::cerr << "Valoare invalida pentru N.\n";
        return 1;
    }

    // 3. Calculam dimensiunea totala de alocat (N pagini)
    size_t allocSize = static_cast<size_t>(N) * pageSize;

    // 4. Alocam memoria folosind VirtualAlloc
    LPVOID p = VirtualAlloc(
        nullptr,              // Adresa sugerata (nullptr = lasa sistemul sa aleaga)
        allocSize,            // Dimensiunea de alocat
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE        // Paginile pot fi citite si scrise
    );

    // Verificam dacă alocarea a reusit
    if (p == nullptr) {
        std::cerr << "Eroare la alocarea memoriei cu VirtualAlloc.\n";
        return 1;
    }

    // Afisam adresa la care a fost alocata memoria
    std::cout << "Memorie alocata la adresa: " << p << std::endl;

     VirtualFree(p, 0, MEM_RELEASE);

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
