#pragma once
#include <iostream>
//#include <deque>
#include <functional> // ��� std::reference_wrapper

#include <cassert> // ��� assert()




class bakterium
{
protected:
	int m_generation;			//����� ���������
	int m_reproduction_coef;	//���������� �����������
	double m_progress;			//��������� ���������� ������������� � ����������
	double m_speed_coef;	    // ��������

public:
	bakterium(int generation = 1, int reproduction_coef = 2, double speed_coef = 1.0);
	virtual ~bakterium();
	friend std::ostream& operator<<(std::ostream &out, const bakterium &b)
	{ 
		return b.print(out); 
	}
	virtual std::ostream& print(std::ostream& out) const = 0; //������� ����� �����������, ��� �� ��������� ��������� ������� ��������

	friend bool operator< (const bakterium &b1, const bakterium &b2); //��� ����������

	int get_reproduction_coef() { return m_reproduction_coef; }
	double get_progress() { return m_progress; }
	double get_generation() const { return m_generation; }
	double get_speed() const { return m_speed_coef; }

};



class bakterium_peasefull : public bakterium
{


	static double m_ageing_coef;    // ���������� ���������� ������������� �� �������� (�������e)
	
public:
	bakterium_peasefull(int generation = 1, double speed_coef = 1.0, int reproduction_coef = 2);


	void ageing();//�������������� ����������� �� �������� (��������)


	~bakterium_peasefull();

	std::ostream& print(std::ostream& out) const override; //��� ���������� ��������� <<


	static double get_ageing_coef() {return m_ageing_coef;}
	static void set_ageing_coef(double ageing_coef);

};




class bakterium_agressiv : public bakterium
{

	static int m_agr_coef;        // ����������, ������� ���� ������ ������ ��������, ��� �� ��������
	bool m_dinnered;			 // ����� �� ��������
public:
	bakterium_agressiv(int generation = 1, double speed_coef = 1.0, int reproduction_coef = 2);


	~bakterium_agressiv();

	 
	std::ostream& print(std::ostream& out) const override; //��� ���������� ��������� <<

	//double get_agr_coef() const { return m_agr_coef; }
	void set_dinnered(bool d);
	bool get_dinnered() const { return m_dinnered; }

	static int get_agr_coef() { return m_agr_coef; }
	static void set_agr_coef(double agr_coef);
	


	/*
	friend bool operator< (const bakterium_peasefull &b1, const bakterium_peasefull &b2); //��� ����������
	

	double get_speed() const { return m_speed_coef; }
	*/

};

