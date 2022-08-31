// T1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using std::cout;
using std::cin;


int main()
{
    std::cout << "Hello World!\n";

    std::cout << "test GitHub\n";

    std::cout << "This version is not main, branch_1" << std::endl;

   // std::cout << "first step, commit it :) " << std::endl;


    //задержка выключения
    cin.clear();
    cin.ignore(32000, '\n');
    cin.get();
    return 0;

}


