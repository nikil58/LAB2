#ifndef LAB2_1_MAIN_MENU_H
#define LAB2_1_MAIN_MENU_H
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
         << "1. Create new file \n"
         << "2. Write data\n"
         << "3. Close file\n"
         << "0. Exit\n\n";
}

#endif //LAB2_1_MAIN_MENU_H
