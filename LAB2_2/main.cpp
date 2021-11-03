#include <iostream>
#include <windows.h>
#include "main_menu.h"

using namespace std;

HANDLE createFile(HANDLE &handleF, HANDLE &handleM){
    cout << "Enter the path where need to create file: ";
    char nameF[MAX_PATH];
    cin.getline(nameF, MAX_PATH);


    handleF = CreateFileA(nameF, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
    if (handleF == INVALID_HANDLE_VALUE) {
        cout << "Error " << GetLastError() << " occurred" << endl;
        return nullptr;
    }

    cout << "Enter map unique name: ";
    char nameM[MAX_PATH];
    cin.getline(nameM, MAX_PATH);

    handleM = CreateFileMappingA(handleF, nullptr, PAGE_READWRITE, 0, 512, nameM);
    if (handleM == nullptr) {
        CloseHandle(handleF);
        cout << "Error " << GetLastError() << " occurred" << endl;
        return nullptr;
    }

    HANDLE address = MapViewOfFile(handleM, FILE_MAP_ALL_ACCESS, 0, 0, 512 );
    if (address == nullptr) {
        CloseHandle(handleM);
        CloseHandle(handleF);
        cout << "Error " << GetLastError() << " occurred" << endl;
        return nullptr;
    }
    cout << "File created successfully" << endl;
    return  address;
}

void write(HANDLE map_address){
    cout << "Enter a string of no more than 512 characters: ";
    char data[512];
    cin.getline(data, MAX_PATH);
    if (strnlen(data, 512)  <= 512) {
        memcpy(map_address, data, strnlen(data,512));
        cout << "Data written successfully" << endl;
    }
    else {
        cout << "Data size is too large for the file" << endl;
    }
}

void close (HANDLE &map_address, HANDLE &map_handle, HANDLE &file_handle){
        UnmapViewOfFile(map_address);
        CloseHandle(map_handle);
        CloseHandle(file_handle);
        file_handle = INVALID_HANDLE_VALUE;
        map_address = nullptr;
        cout << "Projected file closed" << endl;
    }


void ui(){
    char choice;
    HANDLE address;
    HANDLE handleM;
    HANDLE handleF;
    do{
        choice = input(main_menu);
        switch(choice)
        {
            case '1':
            {
                system("cls");
                address = createFile(handleF, handleM);
                system("pause");
                choice = ' ';
                break;
            }
            case '2':
            {
                system("cls");
                if (address) write(address);
                else cout << "First of all you need to create some file" << endl;
                system("pause");
                choice = ' ';
                break;
            }
            case '3':
            {
                system("cls");
                if (address && handleM && handleF) close (address, handleM, handleF);
                else cout << "There is nothing to clear" << endl;
                system("pause");
                choice = ' ';
                break;
            }
            case '0':
            {
                break;
            }
            default:
            {
                cout << "There is no such paragraph!" << endl;
                system("pause");
                break;
            }
        }
    }while (choice!='0');
}
int main()
{
    ui();
    return 0;
}
