#include <iostream>
#include <windows.h>
#include "main_menu.h"

using namespace std;

void read(){
    string map_name;

    cout << "Enter map name that was entered in previous program:\n";
    getline(cin, map_name);

    HANDLE map_handle = OpenFileMappingA(FILE_MAP_ALL_ACCESS, false, map_name.data());
    if (map_handle == nullptr) {
        cout << "Error " << GetLastError() << " occurred" << endl;
        return;
    }

    void* map_address = MapViewOfFile(map_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (map_address == nullptr) {
        cout << "Error " << GetLastError() << " occurred" << endl;
        return;
    }

    string data(static_cast<char*>(map_address));
    cout << "The data what have been found:\n" << data << endl;
}



void ui(){
    char choice;
    do{
        choice = input(main_menu);
        switch(choice)
        {
            case '1':
            {
                system("cls");
                read();
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
