#pragma once
#include <iostream>
#include <deque>


using std::cout;
using std::endl;


class bacterium
{
protected:
	int m_generation_count; //����� ���������
	double m_reproduction_coef; //���������� ����������� ��������

public:
	bacterium(double reproduction_coef)
		: m_reproduction_coef(reproduction_coef)
	{
	}

	friend  std::ostream& operator<<(std::ostream& out, const bacterium& p) //��� �� �������� �������������� ��������
	{  
		p.print(out);
	}

	virtual std::ostream& print(std::ostream& out) const = 0; //������� ���� ����� �����������, ��� ���������� � ��� �� ��������� ��������� ������� ��������


};



class bacterium_peaceful: public bacterium
{
	double m_speed_coef; //��������


public:
	bacterium_peaceful(double speed_coef = 1.0, double reproduction_coef = 2.0)
		: bacterium(reproduction_coef), m_speed_coef(speed_coef)
	{
	}

	std::ostream& print(std::ostream& out) const override;

};


class peaceful_population 
{
	std::deque<bacterium_peaceful &> peace_p //PEACEful_Population 



};