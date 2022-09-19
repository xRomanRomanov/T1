// bacterium2.cpp: ��������� �������� ���������
// ��������� �� ������ � ���������� ��������
// ������ ������������ � �������
// ���������� ������������, ���� ������ � ������� ���� �� �����
// � ������ �������� ���� ��������. ������ ���������� ���� ������ ���� �� �������� ����
// ��� ����������� �������� ������� ����������
// ���� ���:
// 1. ������� ������� (��������, ������ �����) ����������� ��������� ��� ������ ����������
// 2. ����� ���� ������ ���������, ��� �� ��������� ������������ ������� ����� ������


#include "stdafx.h"
#include <iostream>
#include <fstream> //��� ������� � ������
#include <algorithm>

#include "bakterium.h" //������ � ��������� ��������
#include "population.h" //������ � ��������� ������� ���������
#include "file_work.h" //������ � ������� � ��������� �������������


using std::cout;
using std::cin;
using std::endl;

void dinner(population<bakterium_peasefull> &P, population<bakterium_agressiv> &P_agr); // ��� �������� ����������� ���������� ������
void hunger_agr_bact(population<bakterium_agressiv> &P_agr); // ��� �������� �������� ���������� ��������
void bact_optimiz(population<bakterium_peasefull> &P, population<bakterium_agressiv> &P_agr);


int main()
{
	setlocale(NULL, "Russian");//��������� ������� ����

	Bact_INI bact_INI; //�������� ��������� ��� �������� ��������� �����
	read_initial_from_file(bact_INI); //�������� � �� �����


	population<bakterium_peasefull> P(bact_INI.count_peas, bakterium_peasefull(0, bact_INI.m_speed_coef_peas, bact_INI.m_reproduction_coef_peas));
	//P.push_back(bakterium_peasefull(1, 1.2));
	//P.push_back(bakterium_peasefull(1, bact_INI.m_speed_coef_peas*0.8));
	bakterium_peasefull::set_ageing_coef(bact_INI.m_ageing_coef);
	
	population<bakterium_agressiv> P_agr(bact_INI.count_agr, bakterium_agressiv(0, bact_INI.m_speed_coef_agr, bact_INI.m_reproduction_coef_agr));
	//P_agr.push_back(bakterium_agressiv(1, 1.1));
	//P_agr.push_back(bakterium_agressiv(1, 1.1));
	bakterium_agressiv::set_agr_coef(bact_INI.m_agr_coef);


	P.show_speed();
	P_agr.show_speed();
	cout << endl;


	for (int i(1); i <  bact_INI.amount_of_life; ++i)//���� �� ����������
	{
		cout << endl;
		cout << "����� ��������� = " << i << " ������ ��������� = " << P.size() << " ���������� ��������� =  " << P_agr.size() << endl;
		//cout << "m_ageing_coef " << bakterium_peasefull::get_ageing_coef() << endl;
		dinner(P, P_agr);
		

		if (P.size() < 1 || P_agr.size() < 1)
		{
			cout << "���� ����� �� ��������� = " << i << " ������ ��������� = " << P.size() << " ���������� ��������� =  " << P_agr.size() << endl;
			break;
		}


		
		//P.show_speed();
		//P_agr.show_speed();
		
		
		P.next_generation(i);
		P_agr.next_generation(i);

		  
		

		//������� �����������  - ���� ����� ������ ����� ����� ������ ����������, �� �������� ���������� ��������, ���� ������, �� ������� ��������� ������ (� ������ 1 ���� ����)
		//bact_optimiz(P, P_agr);
		// ������ �� ����� ����� ����������� ����� ������ ����))) ���� ����������
	}






	cin.clear();
	cin.ignore(32767, '\n');
	cin.get();
    return 0;
}


void dinner(population<bakterium_peasefull> &P, population<bakterium_agressiv> &P_agr)
{
	//��� ������ ������� ������� ����������
	//�� ����� �������� ��� �������. ������ ���������
	//����� ����������� �������� ���������� � ������ ��������.
	//���� �������� ���������� ������ - ��� �������. ��� - �������

	P.sort();
	//P.show_speed();
	//P_agr.show_speed();

	// ������ ����� ������ � ������� - ����� ��������
	// ���������� ��������� ����� ������ ������, ���� ���������� �������� �� ������ ������ � - ������ ����� �� ���������.

	for (int i(0); i < P_agr.size(); ++i)						
	{
		// TODO ��� ����������� ���� �� m_agr_coef - ���� ���������� ����� ������ ����� ����� ������
		if (P.size() < 1) break;//���� �� �������� ������, ��������))
			if (P_agr.at(i).get_speed() > P.at(0).get_speed()) 	
			{
				P.pop_front(); //������ �����
				//cout << " ����� i = " << i << endl;
			}
			else	//������ �� �������											
			{
				//cout << " �� ����� i = " << i << endl;
				P_agr.at(i).set_dinnered(false); //�������, ��� �������� ��������
			}
			
	}
	cout << endl;

	hunger_agr_bact(P_agr);

}

void hunger_agr_bact(population<bakterium_agressiv>& P_agr)
{

	//������� �������� ������ ��������, ����� ��� ������ ���� ��� �������� ��������
	while (P_agr.at(0).get_dinnered() == false)
		{
			P_agr.pop_front();
		}
	//������ ������ �������� � ������ - ����� (dinnered == true)
	//� �p������� �� �����, ������ ����� �� ������
	//��� ���������� ����������� ������ ��������� ������ ��������
	for (int i(1); i < P_agr.size(); ++i) 
	{
		int j(i);
		while (P_agr.at(j-1).get_dinnered() == true)
		{
			std::swap(P_agr.at(j), P_agr.at(j-1));
			--j;
			if (j < 1) break;
		}
	}
	// ������ ��� �������� � ������ �������. ������ ��)

	while (P_agr.at(0).get_dinnered() == false)
	{
		P_agr.pop_front();
	}
}

void bact_optimiz(population<bakterium_peasefull>& P, population<bakterium_agressiv>& P_agr)
{
	if (P.size()> 2 * P_agr.size())
	{
		double ageing_coef_old = bakterium_peasefull::get_ageing_coef();
		bakterium_peasefull::set_ageing_coef(ageing_coef_old * 0.9);
	}

	if (P.size() < P_agr.size())
	{
		double ageing_coef_old = bakterium_peasefull::get_ageing_coef();
		bakterium_peasefull::set_ageing_coef(ageing_coef_old * 1.2);
	}


}
