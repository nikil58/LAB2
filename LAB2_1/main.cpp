#include <iostream>
#include <windows.h>
#include "main_menu.h"

string stringArch(const WORD& arch);
string protectionFlags(const DWORD& protection);
string memoryFlags(const DWORD& state);
string memoryTypes(const DWORD& type);

using namespace std;

void getSysInfo(){
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    cout << "Hardware information: \n"
         << "Processor architecture: " << stringArch(siSysInfo.wProcessorArchitecture) << '\n'
         << "OEM ID: " << siSysInfo.dwOemId << '\n'
         << "Number of processors: " <<  siSysInfo.dwNumberOfProcessors << '\n'
         << "Page size: " << siSysInfo.dwPageSize << '\n'
         << "Processor type: " << siSysInfo.dwProcessorType << '\n'
         << "Minimum application address: " <<  siSysInfo.lpMinimumApplicationAddress << '\n'
         << "Maximum application address: " <<  siSysInfo.lpMaximumApplicationAddress << '\n'
         << "Active processor mask: " <<  siSysInfo.dwActiveProcessorMask << '\n'
         << "Processor revision: " << siSysInfo.wProcessorRevision << '\n';
}
string stringArch(const WORD& arch)
{
    switch (arch)
    {
        case PROCESSOR_ARCHITECTURE_INTEL:
            return "x86";
        case PROCESSOR_ARCHITECTURE_ARM:
            return "ARM";
        case PROCESSOR_ARCHITECTURE_IA64:
            return "Intel Itanium-based";
        case PROCESSOR_ARCHITECTURE_AMD64:
            return "x64";
        default:
            return "Unknown architecture";
    }
}
#define DIV 1024
// #define DIV 1
char *divisor = "K";
// char *divisor = "";
// Ширина поля, в которой будут печаться цифры
// "%*ld" преобразует аргумент списка в int, и выравнивает вправо.
#define WIDTH 7
void memoryStatus(){
    MEMORYSTATUS stat;
    GlobalMemoryStatus (&stat);

    printf ("The MemoryStatus structure is %ld bytes long.\n",
            stat.dwLength);
    printf ("It should be %d.\n", sizeof (stat));
    printf ("%ld percent of memory is in use.\n",
            stat.dwMemoryLoad);
    printf ("There are %*ld total %sbytes of physical memory.\n",
            WIDTH, stat.dwTotalPhys/DIV, divisor);
    printf ("There are %*ld free %sbytes of physical memory.\n",
            WIDTH, stat.dwAvailPhys/DIV, divisor);
    printf ("There are %*ld total %sbytes of paging file.\n",
            WIDTH, stat.dwTotalPageFile/DIV, divisor);
    printf ("There are %*ld free %sbytes of paging file.\n",
            WIDTH, stat.dwAvailPageFile/DIV, divisor);
    printf ("There are %*lx total %sbytes of virtual memory.\n",
            WIDTH, stat.dwTotalVirtual/DIV, divisor);
    printf ("There are %*lx free %sbytes of virtual memory.\n",
            WIDTH, stat.dwAvailVirtual/DIV, divisor);
}

void addressStatus(){
    MEMORY_BASIC_INFORMATION memoryInfo;
    void* address;
    cout << "Enter the address of the region witch status you want to get" << endl;
    uint32_t input = 0;
    cin >> hex >> input;
    address = reinterpret_cast<void*>(input);

    if (VirtualQuery(address, &memoryInfo, sizeof(memoryInfo)) == 0) {
        cout << "Error " << GetLastError() << " occurred\n";
        return;
    }
    cout << "Allocation base: " << memoryInfo.AllocationBase << '\n'
         << "Base address: " << memoryInfo.BaseAddress << '\n'
         << "Allocation protection: " << protectionFlags(memoryInfo.AllocationProtect) << '\n'
         << "Region size: " << memoryInfo.RegionSize << '\n'
         << "State: " << memoryFlags(memoryInfo.State) << '\n'
         << "Protection: " << protectionFlags(memoryInfo.Protect) << '\n'
         << "Type: " << memoryTypes(memoryInfo.Type) << '\n';
}

string protectionFlags(const DWORD& protection) {
    string str_protection;
    switch (protection) {
        case PAGE_EXECUTE:
            str_protection = "PAGE_EXECUTE";
            break;
        case PAGE_EXECUTE_READ:
            str_protection = "PAGE_EXECUTE_READ";
            break;
        case PAGE_EXECUTE_READWRITE:
            str_protection = "PAGE_EXECUTE_READWRITE";
            break;
        case PAGE_EXECUTE_WRITECOPY:
            str_protection = "PAGE_EXECUTE_WRITECOPY";
            break;
        case PAGE_NOACCESS:
            str_protection = "PAGE_NOACCESS";
            break;
        case PAGE_READONLY:
            str_protection = "PAGE_READONLY";
            break;
        case PAGE_READWRITE:
            str_protection = "PAGE_READWRITE";
            break;
        case PAGE_WRITECOPY:
            str_protection = "PAGE_WRITECOPY";
            break;
        default: return "NONE";
    }
    if ((protection & PAGE_GUARD) == PAGE_GUARD)
        str_protection += " and PAGE_GUARD";
    else if ((protection & PAGE_NOCACHE) == PAGE_NOCACHE)
        str_protection += " and PAGE_NOCACHE";
    else if ((protection & PAGE_WRITECOMBINE) == PAGE_WRITECOMBINE)
        str_protection += " and PAGE_WRITECOMBINE";
    return str_protection;
}

string memoryFlags(const DWORD& state) {
    switch (state) {
        case MEM_COMMIT: return "MEM_COMMIT";
        case MEM_FREE: return "MEM_FREE";
        case MEM_RESERVE: return "MEM_RESERVE";
        default: return "NONE";
    }
}

string memoryTypes(const DWORD& type) {
    switch (type) {
        case MEM_IMAGE: return "MEM_IMAGE";
        case MEM_MAPPED: return "MEM_MAPPED";
        case MEM_PRIVATE: return "MEM_PRIVATE";
        default: return "NONE";
    }
}

void reserveRegion (const bool& entered){
    void* base_address;
    void* address = nullptr;
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    if (entered) {
        cout << "Enter the address what need to be reserved" << endl;
        uint32_t input = 0;
        cin >> hex >> input;
        address = reinterpret_cast<void*>(input);
    }
    base_address = VirtualAlloc(address, siSysInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (base_address != nullptr) {
        cout << "Allocation successful. Base address: " << base_address << '\n';
    }
    else
        cout << "Error " << GetLastError() << " occurred\n";

}

void allocateRegion (const bool& entered){
    void* base_address;
    void* address = nullptr;
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    if (entered) {
        cout << "Enter the address what need to be reserved and allocated" << endl;
        uint32_t input = 0;
        cin >> hex >> input;
        address = reinterpret_cast<void*>(input);
    }
    base_address = VirtualAlloc(address, siSysInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (base_address != nullptr) {
        cout << "Allocation successful. Base address: " << base_address << '\n';
    }
    else
        cout << "Error " << GetLastError() << " occurred\n";

}

void setProtectionFlag(const DWORD& protection) {
    void* address;
    DWORD old_protection;
    cout << "Enter the address what need to be changed protections flags" << endl;
    uint32_t input = 0;
    cin >> hex >> input;
    address = reinterpret_cast<void*>(input);
    if (VirtualProtect(address, 4, protection, &old_protection))
        cout << "Protection changed successfully! Old protection: " << protectionFlags(old_protection) << '\n';
    else
        cout << "Error " << GetLastError() << " occurred\n";
}

void freeRegion() {
    uint32_t input = 0;
    void* address;
    cout << "Enter the address what need to be free" << endl;
    cin >> hex >> input;
    address = reinterpret_cast<void*>(input);
    if (VirtualFree(address, 0, MEM_RELEASE))
        cout << "Memory free successfully\n";
    else
        cout << "Error " << GetLastError() << " occurred\n";
}

void writeData(){
    void* address;
    string input_d;
    DWORD protection;
    char* p_data;
    MEMORY_BASIC_INFORMATION memoryInfo;
    uint32_t input_a = 0;
    cout << "Enter the address where data will be written" << endl;
    cin >> hex >> input_a;
    address = reinterpret_cast<void*>(input_a);
    if (VirtualQuery(address, &memoryInfo, sizeof(memoryInfo)) == 0) {
        cout << "Error " << GetLastError() << " occurred\n";
        return;
    }
    protection = PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
    if ((memoryInfo.AllocationProtect & protection) == 0) {
        cout << "Memory protection level doesn't allow writing\n";
        return;
    }
    cout << "Enter your data:\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input_d);
    p_data = new char[input_d.length() + 1];
    strcpy_s(p_data, input_d.length() + 1, input_d.c_str());
    if (memcpy_s(address, input_d.length() + 1, p_data, input_d.length() + 1) != 0) {
        cout << "Error occurred\n";
        delete[] p_data;
        return;

    }
    delete[] p_data;
    cout << "Data written successfully\n" << "You wrote the next string: ";
    p_data = static_cast<char*>(address);
    cout << p_data << endl;
}

void ui(){
    char choice;
    do{
        choice = input(main_menu);
        switch (choice)
        {
            case '1':
            {
                system("cls");
                getSysInfo();
                system("pause");
                choice = ' ';
                break;
            }
            case '2':
            {
                system("cls");
                memoryStatus();
                system("pause");
                choice = ' ';
                break;
            }
            case '3':
            {
                system("cls");
                addressStatus();
                system("pause");
                choice = ' ';
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case '4':
            {
                do{
                    choice = input(allocateRegion);
                    switch (choice)
                    {
                        case '1':
                        {
                            reserveRegion(1);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '2':
                        {
                            reserveRegion(0);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '3':
                        {
                            allocateRegion(1);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '4':
                        {
                            allocateRegion(0);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                choice = ' ';
                break;
            }
            case '5':
            {
                do{
                    choice = input(protectionMenu);
                    switch (choice)
                    {
                        case '1':
                        {
                            setProtectionFlag(PAGE_NOACCESS);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }

                        case '2':
                        {
                            setProtectionFlag(PAGE_READONLY);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '3':
                        {
                            setProtectionFlag(PAGE_READWRITE);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '4':
                        {
                            setProtectionFlag(PAGE_WRITECOPY);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '5':
                        {
                            setProtectionFlag(PAGE_EXECUTE);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '6':
                        {
                            setProtectionFlag(PAGE_EXECUTE_READ);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '7':
                        {
                            setProtectionFlag(PAGE_EXECUTE_READWRITE);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '8':
                        {
                            setProtectionFlag(PAGE_EXECUTE_WRITECOPY);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '9':
                        {
                            setProtectionFlag(PAGE_GUARD);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        }
                        case '10':
                        {
                            setProtectionFlag(PAGE_NOCACHE);
                            system("pause");
                            choice = ' ';
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                choice = ' ';
                break;
            }
            case '6':
            {
                system("cls");
                freeRegion();
                system("pause");
                choice = ' ';
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            case '7':
            {
                system("cls");
                writeData();
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
    } while (choice != '0');
}
int main()
{
    ui();
    return 0;
}

