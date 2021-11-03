
#ifndef LABA1_MAIN_MENU_H
#define LABA1_MAIN_MENU_H

using namespace std;


char input(void (*func)()){
    char choice;
    char c;
    int i;
    system("cls");
    func();
        cout << "Select paragraph" << endl;
        choice=getchar();
        i = 0;
        if (choice!='\n') while ((c = getchar()) != '\n')i++;
        if (i) choice = '-';
        return choice;
}


void main_menu(){
    cout << "Main Menu\n"
         << "-------------------------------------------------\n"
         << "1. System info\n"
         << "2. Virtual Memory status\n"
         << "3. Address status\n"
         << "4. Allocate region\n"
         << "5. Region protection\n"
         << "6. Free region\n"
         << "7. Write data into address\n"
         << "0. Exit\n\n";
}

void allocateRegion(){
    cout << "Let's work with Allocation of Regions!\n"
         << "------------------------------------------------------------\n"
         << "1. Reserve region manually\n"
         << "2. Reserve region automatically\n"
         << "3. Reserve and allocate region manually\n"
         << "4. Reserve and allocate region automatically\n"
         << "0. Return\n\n";
}

void protectionMenu(){
    cout << "Let's work with region's protection! Select any flag\n"
         << "------------------------------------------------------------------\n"
         << "1. PAGE_NOACCESS\n"
         << "2. PAGE_READONLY \n"
         << "3. PAGE_READWRITE\n"
         << "4. PAGE_WRITECOPY\n"
         << "5. PAGE_EXECUTE\n"
         << "6. PAGE_EXECUTE_READ\n"
         << "7. PAGE_EXECUTE_READWRITE \n"
         << "8. PAGE_EXECUTE_WRITECOPY\n"
         << "9. PAGE_GUARD\n"
         << "10. PAGE_NOCACHE\n"
         << "0. Return\n\n";
}


#endif //LABA1_MAIN_MENU_H
