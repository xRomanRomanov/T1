#pragma once


struct Bact_INI
{

	int count_peas;					 //��������� ���������� ������ �������� 
	int m_reproduction_coef_peas;  	 //���������� �����������  ������ ��������
	double m_speed_coef_peas;	     // �������� ������ ��������
	double m_ageing_coef;			 // ���������� ���������� ������������� �� �������� (�������e)

	int count_agr;					//��������� ���������� ������ �������� 
	int m_reproduction_coef_agr;	//���������� ����������� ������ ��������
	double m_speed_coef_agr;	    // �������� ������ ��������
	int m_agr_coef;				    // ����������, ������� ���� ������ ������ ��������, ��� �� ��������
	
	int amount_of_life;				//����� ��������� ������ (���������)

};


void read_initial_from_file(Bact_INI &bact_INI); //��� ��������� - ��� ��������� ���������� �������



