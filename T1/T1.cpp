// bacterium2.cpp: Симулятор замнутой популяции
// состоящей из мирных и агресивных бактерий
// мирные размножаются и стареют
// агресивные размножаются, едят мирных и умирают если не поели
// у каждой бактерии есть скорость. причем агресивные едят только если их скорость выше
// при размножении скорость батерий возрастает
// цели две:
// 1. сколько времени (итераций, циклов жизни) продержится популяции при заданы параметрах
// 2. какие надо задать параметры, что бы популяция продержалась заданое число циклов


//#include "stdafx.h"
#include <iostream>
#include <fstream> //для доступа к файлам
#include <algorithm>

#include "bakterium.h" //классы с описанием бактерий
#include "population.h" //шаблон с описанием массива популяции
#include "file_work.h" //работа с файлами и начальная инициализация


using std::cout;
using std::cin;
using std::endl;

void dinner(population<bakterium_peasefull>& P, population<bakterium_agressiv>& P_agr); // для поедания агресивными бактериями мирных
void hunger_agr_bact(population<bakterium_agressiv>& P_agr); // для удаления голодных агресивных бактерий
void bact_optimiz(population<bakterium_peasefull>& P, population<bakterium_agressiv>& P_agr);


int main()
{
	setlocale(NULL, "Russian");//поддержка русских букв

	Bact_INI bact_INI; //создадим структуру для хранения начальных даных
	read_initial_from_file(bact_INI); //заполним её из файла
	
	population<bakterium_peasefull> P(bact_INI.count_peas, bakterium_peasefull(0, bact_INI.m_speed_coef_peas, bact_INI.m_reproduction_coef_peas));
	//population<bakterium_peasefull> P(bact_INI.count_peas, B_P);
	//P.push_back(bakterium_peasefull(1, 1.2));
	//bakterium_peasefull B_P(0, bact_INI.m_speed_coef_peas * 0.8);
	P.push_back(bakterium_peasefull(0, bact_INI.m_speed_coef_peas * 0.8) );//добавим хилую бактерию, для прокормки хищьных
	bakterium_peasefull::set_ageing_coef(bact_INI.m_ageing_coef);

	bakterium_agressiv B_A(0, bact_INI.m_speed_coef_peas, bact_INI.m_reproduction_coef_peas);
	//population<bakterium_agressiv> P_agr(bact_INI.count_agr, B_A);

	population<bakterium_agressiv> P_agr(bact_INI.count_agr, bakterium_agressiv(0, bact_INI.m_speed_coef_agr, bact_INI.m_reproduction_coef_agr));
	//P_agr.push_back(bakterium_agressiv(1, 1.1));
	//P_agr.push_back(bakterium_agressiv(1, 1.1));
	bakterium_agressiv::set_agr_coef(bact_INI.m_agr_coef);


	P.show_speed();
	cout << endl;
	P_agr.show_speed();
	cout << endl;


	for (int i(1); i < bact_INI.amount_of_life; ++i)//цикл по поколениям
	{
		cout << endl;
		cout << "Старт поколения = " << i << " мирная популяция = " << P.size() << " агресивная популяция =  " << P_agr.size() << endl;
		//cout << "m_ageing_coef " << bakterium_peasefull::get_ageing_coef() << endl;
		dinner(P, P_agr);


		if (P.size() < 1 || P_agr.size() < 1)
		{
			cout << "Всех съели на поколении = " << i << " мирная популяция = " << P.size() << " агресивная популяция =  " << P_agr.size() << endl;
			break;
		}



		//P.show_speed();
		//P_agr.show_speed();


		P.next_generation(i);
		P_agr.next_generation(i);




		//сделаем оптимизацию  - если число мирных стало много больше агресивных, то увеличим коэфициент старения, если меньше, то сделаем коэфицинт больше (и больше 1 если надо)
		//bact_optimiz(P, P_agr);
		// почему то после такой оптимизации стало только хуже))) пока закоментим
	}






	cin.clear();
	cin.ignore(32767, '\n');
	cin.get();
	return 0;
}


void dinner(population<bakterium_peasefull>& P, population<bakterium_agressiv>& P_agr)
{
	//для начала сделаем простую реализацию
	//на входе получаем два массива. Мирных сортируем
	//затем сравниватся скорость агресивной и мирной бактерий.
	//если скорость агресивной больше - она съедает. нет - умирает

	P.sort();
	//P.show_speed();
	//P_agr.show_speed();

	// теперь самая первая в массиве - самая медленая
	// достаточно проверить самую первую мирную, если агресивная бактерия не смогла съесть её - других можно не проверять.

	for (int i(0); i < P_agr.size(); ++i)
	{
		// TODO еще реализовать цикл по m_agr_coef - ведь агресивная может съесть более одной мирной
		if (P.size() < 1) break;//если не осталась никого, закончим))
		if (P_agr.at(i).get_speed() > P.at(0).get_speed())
		{
			P.pop_front(); //мирную съели
			//cout << " съели i = " << i << endl;
		}
		else	//съесть не удалось											
		{
			//cout << " не съели i = " << i << endl;
			P_agr.at(i).set_dinnered(false); //отметим, что бактерия голодная
		}

	}
	cout  << endl;

	hunger_agr_bact(P_agr);

}

void hunger_agr_bact(population<bakterium_agressiv>& P_agr)
{


	//сначало проверим первые элементы, вдруг там подряд идет ряд голодных бактерий
	while (P_agr.at(0).get_dinnered() == false)
	{
		if (P_agr.size() < 2) return;//если остается 1, то вылетает на следующей операции.
		P_agr.pop_front();
	}

	//теперь первая бактерия в списке - сытая (dinnered == true)
	//её пpоверять не будем, начнем сразу со второй
	//для тренировки отсортируем массив вариацией метода пузырька
	for (int i(1); i < P_agr.size(); ++i)
	{
		int j(i);
		while (P_agr.at(j - 1).get_dinnered() == true)
		{
			std::swap(P_agr.at(j), P_agr.at(j - 1));
			--j;
			if (j < 1) break;
		}
	}
	// теперь все голодные в начале массива. Удалим их)
	while (P_agr.at(0).get_dinnered() == false)
	{
		P_agr.pop_front();
	}
}

void bact_optimiz(population<bakterium_peasefull>& P, population<bakterium_agressiv>& P_agr)
{
	if (P.size() > 2 * P_agr.size())
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
