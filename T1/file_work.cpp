#include "stdafx.h"
#include <iostream>
#include <fstream> //��� ������� � ������
#include <string>
#include "file_work.h"


using std::cout;
using std::cin;
using std::endl;


void read_initial_from_file(Bact_INI & bact_INI)  //��� ��������� - ��� ��������� ���������� �������
{

	while (1)
	{

		std::ifstream openFile("INI.txt");

		if (!openFile) // ���� �� ������ �������
		{
			std::cerr << "�� ������ ������� ���� INI.txt ";
			std::exit(1);
		}

		std::string strInput;
		std::getline(openFile, strInput);  //������ ������ ������ (��������)

										   //������ ������ �� ������� (�����)
		openFile >> bact_INI.count_peas; //��������� ���������� ������ ��������
		std::getline(openFile, strInput);//����� ���������� ��� �������� � ������ � �������� �� ��������� ������
		openFile >> bact_INI.m_reproduction_coef_peas; //���������� ����������� ������
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_speed_coef_peas;// �������� ������ ��������
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_ageing_coef;//���������� ���������� ������������� �� �������� (�������e)
		std::getline(openFile, strInput);


		std::getline(openFile, strInput); //������  ������ (��������)
		std::getline(openFile, strInput); //������  ������ (��������)

		openFile >> bact_INI.count_agr; //��������� ���������� ������ ��������
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_reproduction_coef_agr; //���������� ����������� ������
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_speed_coef_agr; // �������� ������ ��������
		std::getline(openFile, strInput);
		openFile >> bact_INI.m_agr_coef; //����������, ������� ���� ������ ������ ��������, ��� �� ��������
		std::getline(openFile, strInput);

		std::getline(openFile, strInput); //������  ������ (��������)
		openFile >> bact_INI.amount_of_life; //����� ��������� ������ (���������)
		std::getline(openFile, strInput);
		
		//TODO - ������� �� ������� �������� �����

		//������ ���������. ������� �� �����.

		cout << "\n ��������� ������ ��������:" << "\n";
		cout << "��������� ���������� ������ �������� =\t \t \t" << bact_INI.count_peas << "\n";
		cout << "���������� ����������� ������ = \t \t \t" << bact_INI.m_reproduction_coef_peas << "\n";
		cout << "�������� ������ �������� = \t  \t \t \t" << bact_INI.m_speed_coef_peas << "\n";
		cout << "���������� ������������� �� �������� (�������e) = \t" << bact_INI.m_ageing_coef << "\n";

		cout << " \n ��������� ������ ��������: " << "\n";
		cout << "��������� ���������� ������ �������� = \t\t \t" << bact_INI.count_agr << "\n";
		cout << "���������� ����������� ������ =  \t\t \t" << bact_INI.m_reproduction_coef_agr << "\n";
		cout << "�������� ������ �������� = \t\t  \t \t" << bact_INI.m_speed_coef_agr << endl;
		cout << "������� ���� ������ ������ ��������, ��� �� �������� \t" << bact_INI.m_agr_coef << endl;

		cout << " \n ����� ��������� ������ (���������): " << bact_INI.amount_of_life << endl;

		cout << " \n ��� ���������? (1 - ��, 0 - ���������� ����)" << endl;
		int user_choice{ 0 };
		cin.clear(); //������� �� ������ ������

		cin >> user_choice;
		if (std::cin.fail()) //�������� ����������������� �����
		{
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			cout << "\n ��������� ����, ���������� ��� ��� " << endl;
			//user_choice = 0;
		}
		else if (user_choice != 1 && user_choice != 0)
		{
			cout << "\n �� ����� ������������ �����. ������� '1' ��� '0' " << endl;
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
				cout << "\n ���� �������� ������ " << endl;
				std::cin.ignore(32767, '\n');
			}


		}



		
	}



}
