#include <iostream>
#include "consoleUtils.hpp"

using namespace std;

void pauseConsole()
{
    cout << "Pulsa Enter para continuar" << endl;
    cin.get();  
}

void clearConsole() {
    #ifdef __unix__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN64)
        system("cls");
    #endif
}