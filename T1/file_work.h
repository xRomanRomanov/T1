#pragma once


struct Bact_INI
{

	int count_peas;					 //начальное количество мирных бактерий 
	int m_reproduction_coef_peas;  	 //коэфициент размножения  мирных бактерий
	double m_speed_coef_peas;	     // скорость мирных бактерий
	double m_ageing_coef;			 // коэфициент уменьшения характеристик со временем (старениe)

	int count_agr;					//начальное количество хищных бактерий 
	int m_reproduction_coef_agr;	//коэфициент размножения хищных бактерий
	double m_speed_coef_agr;	    // скорость хищных бактерий
	int m_agr_coef;				    // голодность, сколько надо съесть мирных бактерий, что бы наесться
	
	int amount_of_life;				//число жизненных циклов (поколений)

};


void read_initial_from_file(Bact_INI &bact_INI); //тут структура - это результат выполнения функции



