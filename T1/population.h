#pragma once
#include <iostream>
#include <deque>
#include <algorithm>
#include <cassert> // для assert()

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


	population_base(int start_amount_population, T &b1) //наполнить массив бактериями в количестве "start_amount_population" штук
	{
		for (int i(0); i < start_amount_population; ++i)
		{
			population_massiv.push_back(b1);
		}
	}

	population_base(int start_amount_population, T&& b1) //наполнить массив бактериями в количестве "start_amount_population" штук
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
		assert(index >= 0 && index < population_massiv.size()); //небольшая проверка диапазона.
																//TODO - возможо в будущем имет смысл заменить на исключение
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

	void push_back(const T &b1) //может тут экономнее будет принимать ссылку на r-value (&&b1), что бы перемещать объект, а не копировать?
	{
		population_massiv.push_back(b1);
	}

	void push_front(const T &b1)
	{
		population_massiv.push_front(b1);
	}


	// TODO для методов show_speed и show_generation надо бы переделать формат вывода
	// чтобы была табличка вида "скорость - число бактерий", а не как сейчас
	// проблема в том, что когда число батреий переваливает за 100 - такой вывод становится не информативным
	void show_speed() //вывод скорости для каждой бактерии из популяции
	{
		for (T &b : population_massiv)
		{
			cout << b.get_speed() << "  ";
		}
		cout << endl;
	}
	
	void show_generation()//вывод номера поколения для каждой бактерии из популяции
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


	//каждая из оставшихся в живых бактерий рождает "m_reproduction_coef" новых
	//при этом увеличиватся скорость новой бактерии
	void next_generation(int actual_generation) //переход на новое поколение (рождение новых батерий)
	{
		int i_max = population_massiv.size(); //запомним размер популяции до того, как начали рождаться новые бактерии 
		int r = population_massiv.at(0).get_reproduction_coef(); //коэфициент размножения бактерии данного типа
		for (int i(0); i < i_max; ++i)
		{
			double new_speed = (population_massiv.at(i).get_speed()) * (population_massiv.at(i).get_progress()); // бактерия размножается
			// TODO надо бы еще предусмотреть защиту от переполнения. на всякий случай
			// например когда значение new_speed переваливает за 10е7, то делим его на 10е7.
			// оно растет на порядок каждые 10 поколений, начит преполнится через 3000 поколений примерно.
			for (int j(1); j < population_massiv.at(i).get_reproduction_coef(); ++j) //новые бактерии добавляются в популяцию
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

template <> //непонятная ошибка. без специализации ругается на конструктор
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




template <> //специализируем шаблон для мирных бактерий, с учетом старения
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

	void next_generation(int actual_generation) //переход на новое поколение (рождение новых батерий и старение старых)
	{
		int i_max = population_massiv.size(); //запомним размер популяции до того, как начали рождаться новые бактерии 
		int r = population_massiv.at(0).get_reproduction_coef(); //коэфициент размножения бактерии данного типа
		for (int i(0); i < i_max; ++i)
		{
			double new_speed = (population_massiv.at(i).get_speed()) * (population_massiv.at(i).get_progress()); //сначала бактерия размножается
			population_massiv.at(i).ageing();																	 //потом стареет

			for (int j(1); j < population_massiv.at(i).get_reproduction_coef(); ++j) //новые бактерии добавляются в популяцию
			{
				population_massiv.push_back(bakterium_peasefull(actual_generation, new_speed, r));
			}
		}

	}


};


