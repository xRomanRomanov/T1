#pragma once
#include <iostream>
//#include <deque>
#include <functional> // для std::reference_wrapper

#include <cassert> // для assert()




class bakterium
{
protected:
	int m_generation;			//номер поколения
	int m_reproduction_coef;	//коэфициент размножения
	double m_progress;			//коэфицинт увеличения характеристик с поколением
	double m_speed_coef;	    // скорость

public:
	bakterium(int generation = 1, int reproduction_coef = 2, double speed_coef = 1.0);
	virtual ~bakterium();
	friend std::ostream& operator<<(std::ostream &out, const bakterium &b)
	{ 
		return b.print(out); 
	}
	virtual std::ostream& print(std::ostream& out) const = 0; //сделаем класс абстрактным, что бы запретить создавать простые бактерии

	friend bool operator< (const bakterium &b1, const bakterium &b2); //для сортировки

	int get_reproduction_coef() { return m_reproduction_coef; }
	double get_progress() { return m_progress; }
	double get_generation() const { return m_generation; }
	double get_speed() const { return m_speed_coef; }

};



class bakterium_peasefull : public bakterium
{


	static double m_ageing_coef;    // коэфициент уменьшения характеристик со временем (старениe)
	
public:
	bakterium_peasefull(int generation = 1, double speed_coef = 1.0, int reproduction_coef = 2);


	void ageing();//характеристики уменьшаются со временем (старение)


	~bakterium_peasefull();

	std::ostream& print(std::ostream& out) const override; //для перегрузки оператора <<


	static double get_ageing_coef() {return m_ageing_coef;}
	static void set_ageing_coef(double ageing_coef);

};




class bakterium_agressiv : public bakterium
{

	static int m_agr_coef;        // голодность, сколько надо съесть мирных бактерий, что бы наесться
	bool m_dinnered;			 // поела ли бактерия
public:
	bakterium_agressiv(int generation = 1, double speed_coef = 1.0, int reproduction_coef = 2);


	~bakterium_agressiv();

	 
	std::ostream& print(std::ostream& out) const override; //для перегрузки оператора <<

	//double get_agr_coef() const { return m_agr_coef; }
	void set_dinnered(bool d);
	bool get_dinnered() const { return m_dinnered; }

	static int get_agr_coef() { return m_agr_coef; }
	static void set_agr_coef(double agr_coef);
	


	/*
	friend bool operator< (const bakterium_peasefull &b1, const bakterium_peasefull &b2); //для сортировки
	

	double get_speed() const { return m_speed_coef; }
	*/

};

