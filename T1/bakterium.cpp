//#include "stdafx.h"
#include <iostream>
#include "bakterium.h"
#include <cassert> // для assert()
#include <utility> // для swap

using std::cout;
using std::cin;
using std::endl;

bakterium::bakterium(int generation, int reproduction_coef, double speed_coef)
	:m_generation(generation), m_reproduction_coef(reproduction_coef), m_speed_coef(speed_coef), m_progress(1.1)
{
}


bakterium::~bakterium()
{
}





bakterium_peasefull::bakterium_peasefull(int generation , double speed_coef, int reproduction_coef)
	:bakterium(generation, reproduction_coef, speed_coef)
{
}

double bakterium_peasefull::m_ageing_coef = 0.95;

void bakterium_peasefull::ageing()
{
	m_speed_coef *= m_ageing_coef;
}

bakterium_peasefull::~bakterium_peasefull()
{
}

std::ostream & bakterium_peasefull::print(std::ostream & out) const
{
	{
		out << " bakterium peasefull" << "\n";
		out << " generation № " << m_generation << "\n";
		out << " reproduction coef = " << m_reproduction_coef << "\n";
		out << " speed coef = " << m_speed_coef << "\n";
		return out;
	}
}

void bakterium_peasefull::set_ageing_coef(double ageing_coef)
{
	m_ageing_coef = ageing_coef;
}





bool operator<(const bakterium & b1, const bakterium & b2)
{
	return  b1.m_speed_coef < b2.m_speed_coef;
}





bakterium_agressiv::bakterium_agressiv(int generation, double speed_coef, int reproduction_coef)
	:bakterium(generation, reproduction_coef, speed_coef),  m_dinnered(true)
{
}

int bakterium_agressiv::m_agr_coef = 1;

bakterium_agressiv::~bakterium_agressiv()
{
}

std::ostream & bakterium_agressiv::print(std::ostream & out) const
{
	out << " bakterium agressiv" << "\n";
	out << " generation № " << m_generation << "\n";
	out << " reproduction coef = " << m_reproduction_coef << "\n";
	out << " speed coef = " << m_speed_coef << "\n";
	out << " agr coef = " << m_agr_coef << "\n";
	return out;
}

void bakterium_agressiv::set_dinnered(bool d)
{
	m_dinnered = d;
}

void bakterium_agressiv::set_agr_coef(int agr_coef)
{
	m_agr_coef = agr_coef;

}
