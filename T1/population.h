#pragma once
#include <iostream>
#include <deque>
#include <algorithm>
#include <cassert> // ��� assert()

using std::cout;
using std::cin;
using std::endl;

template <class T>
class population_base
{

protected:
	std::deque<T> population_massiv;


public:

	population_base()
	{

	}


	population_base(int start_amount_population, T &b1) //��������� ������ ���������� � ���������� "start_amount_population" ����
	{
		for (int i(0); i < start_amount_population; ++i)
		{
			population_massiv.push_back(b1);
		}
	}

	population_base(int start_amount_population, T&& b1) //��������� ������ ���������� � ���������� "start_amount_population" ����
	{
		for (int i(0); i < start_amount_population; ++i)
		{
			population_massiv.push_back(b1);
		}
	}


	~population_base()
	{
	}

	T& operator[] (const int index)
	{
		return population_massiv[index];
	}


	T& at(const int index)
	{
		assert(index >= 0 && index < population_massiv.size()); //��������� �������� ���������.
																//TODO - ������� � ������� ���� ����� �������� �� ����������
		return population_massiv.at(index);
	}



	int size()
	{
		return  population_massiv.size();
	}

	void pop_front()
	{
		population_massiv.pop_front();
	}

	void pop_back()
	{
		population_massiv.pop_back();
	}

	void push_back(const T &b1) //����� ��� ��������� ����� ��������� ������ �� r-value (&&b1), ��� �� ���������� ������, � �� ����������?
	{
		population_massiv.push_back(b1);
	}

	void push_front(const T &b1)
	{
		population_massiv.push_front(b1);
	}


	// TODO ��� ������� show_speed � show_generation ���� �� ���������� ������ ������
	// ����� ���� �������� ���� "�������� - ����� ��������", � �� ��� ������
	// �������� � ���, ��� ����� ����� ������� ������������ �� 100 - ����� ����� ���������� �� �������������
	void show_speed() //����� �������� ��� ������ �������� �� ���������
	{
		for (T &b : population_massiv)
		{
			cout << b.get_speed() << "  ";
		}
		cout << endl;
	}
	
	void show_generation()//����� ������ ��������� ��� ������ �������� �� ���������
	{
		for (T &b : population_massiv)
		{
			cout << b.get_generation() << "  ";
		}
		cout << endl;
	}

	void sort()
	{
		std::sort(population_massiv.begin(), population_massiv.end());
	}


	//������ �� ���������� � ����� �������� ������� "m_reproduction_coef" �����
	//��� ���� ������������ �������� ����� ��������
	void next_generation(int actual_generation) //������� �� ����� ��������� (�������� ����� �������)
	{
		int i_max = population_massiv.size(); //�������� ������ ��������� �� ����, ��� ������ ��������� ����� �������� 
		int r = population_massiv.at(0).get_reproduction_coef(); //���������� ����������� �������� ������� ����
		for (int i(0); i < i_max; ++i)
		{
			double new_speed = (population_massiv.at(i).get_speed()) * (population_massiv.at(i).get_progress()); // �������� ������������
			// TODO ���� �� ��� ������������� ������ �� ������������. �� ������ ������
			// �������� ����� �������� new_speed ������������ �� 10�7, �� ����� ��� �� 10�7.
			// ��� ������ �� ������� ������ 10 ���������, ����� ����������� ����� 3000 ��������� ��������.
			for (int j(1); j < population_massiv.at(i).get_reproduction_coef(); ++j) //����� �������� ����������� � ���������
			{
				population_massiv.push_back(T(actual_generation, new_speed, r));
			}
		}

	}
};


template <class T>
class population :public population_base <T>
{
public:
	population(int start_amount_population, T &b1)
		:population_base(start_amount_population, b1)
	{
		
	}

	population(int start_amount_population, T&& b1)
		:population_base(start_amount_population, b1)
	{
		
	}
};

template <> //���������� ������. ��� ������������� �������� �� �����������
class population<bakterium_agressiv> :public population_base <bakterium_agressiv>
{
public:
	population(int start_amount_population, bakterium_agressiv& b1)
		:population_base(start_amount_population, b1)
	{

	}

	population(int start_amount_population, bakterium_agressiv&& b1)
		:population_base(start_amount_population, b1)
	{

	}
};




template <> //�������������� ������ ��� ������ ��������, � ������ ��������
class population<bakterium_peasefull> :public population_base <bakterium_peasefull>
{
public:

	population(int start_amount_population, bakterium_peasefull &b1)
		:population_base(start_amount_population, b1)
	{

	}

	population(int start_amount_population, bakterium_peasefull&& b1)
		:population_base(start_amount_population, b1)
	{

	}

	void next_generation(int actual_generation) //������� �� ����� ��������� (�������� ����� ������� � �������� ������)
	{
		int i_max = population_massiv.size(); //�������� ������ ��������� �� ����, ��� ������ ��������� ����� �������� 
		int r = population_massiv.at(0).get_reproduction_coef(); //���������� ����������� �������� ������� ����
		for (int i(0); i < i_max; ++i)
		{
			double new_speed = (population_massiv.at(i).get_speed()) * (population_massiv.at(i).get_progress()); //������� �������� ������������
			population_massiv.at(i).ageing();																	 //����� �������

			for (int j(1); j < population_massiv.at(i).get_reproduction_coef(); ++j) //����� �������� ����������� � ���������
			{
				population_massiv.push_back(bakterium_peasefull(actual_generation, new_speed, r));
			}
		}

	}


};


