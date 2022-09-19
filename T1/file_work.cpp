#include "stdafx.h"
#include <iostream>
#include <fstream> //для доступа к файлам
#include <string>
#include "file_work.h"


using std::cout;
using std::cin;
using std::endl;


void read_initial_from_file(Bact_INI & bact_INI)  //тут структура - это результат выполнения функции
{

	while (1)
	{

		std::ifstream openFile("INI.txt");

		if (!openFile) // если не смогли открыть
		{
			std::cerr << "не смогли открыть файл INI.txt ";
			std::exit(1);
		}

		std::string strInput;
		std::getline(openFile, strInput);  //читаем первую строку (ненужную)

										   //теперь читаем до пробела (цифру)
		openFile >> bact_INI.count_peas; //начальное количество мирных бактерий
		std::getline(openFile, strInput);//потом дочитываем что осталось в строке и переодим на следующую строку
		openFile >> bact_INI.m_reproduction_coef_peas; //коэфициент размножения мирных
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_speed_coef_peas;// скорость мирных бактерий
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_ageing_coef;//коэфициент уменьшения характеристик со временем (старениe)
		std::getline(openFile, strInput);


		std::getline(openFile, strInput); //читаем  строку (ненужную)
		std::getline(openFile, strInput); //читаем  строку (ненужную)

		openFile >> bact_INI.count_agr; //начальное количество хищных бактерий
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_reproduction_coef_agr; //коэфициент размножения хищных
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_speed_coef_agr; // скорость хищных бактерий
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_agr_coef; //голодность, сколько надо съесть мирных бактерий, что бы наесться
		std::getline(openFile, strInput);

		std::getline(openFile, strInput); //читаем  строку (ненужную)
		openFile >> bact_INI.amount_of_life; //число жизненных циклов (поколений)
		std::getline(openFile, strInput);
		
		//TODO - неплохо бы сделать проверку ввода

		//чтение закончено. Выведем на экран.

		cout << "\n Параметры мирных бактерий:" << "\n";
		cout << "начальное количество мирных бактерий =\t \t \t" << bact_INI.count_peas << "\n";
		cout << "коэфициент размножения мирных = \t \t \t" << bact_INI.m_reproduction_coef_peas << "\n";
		cout << "скорость мирных бактерий = \t  \t \t \t" << bact_INI.m_speed_coef_peas << "\n";
		cout << "уменьшение характеристик со временем (старениe) = \t" << bact_INI.m_ageing_coef << "\n";

		cout << " \n Параметры хищных бактерий: " << "\n";
		cout << "начальное количество хищных бактерий = \t\t \t" << bact_INI.count_agr << "\n";
		cout << "коэфициент размножения хищных =  \t\t \t" << bact_INI.m_reproduction_coef_agr << "\n";
		cout << "скорость хищных бактерий = \t\t  \t \t" << bact_INI.m_speed_coef_agr << endl;
		cout << "сколько надо съесть мирных бактерий, что бы наесться \t" << bact_INI.m_agr_coef << endl;

		cout << " \n число жизненных циклов (поколений): " << bact_INI.amount_of_life << endl;

		cout << " \n Все нормально? (1 - да, 0 - перечитать файл)" << endl;
		int user_choice{ 0 };
		cin.clear(); //сбросим на всякий случай

		cin >> user_choice;
		if (std::cin.fail()) //проверка пользовательского ввода
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			cout << "\n неудачный ввод, попробуйте еще раз " << endl;
			//user_choice = 0;
		}
		else if (user_choice != 1 && user_choice != 0)
		{
			cout << "\n вы ввели неправильную цифру. введите '1' или '0' " << endl;
			//user_choice = 0;
			std::cin.ignore(32767, '\n');

		}
		else
		{
			
			if (user_choice == 1)
			{
				break;
			}
			else
			{
				cout << "\n Файл прочитан заново " << endl;
				std::cin.ignore(32767, '\n');
			}


		}



		
	}



}
