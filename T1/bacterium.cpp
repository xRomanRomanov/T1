#include "bacterium.h"



std::ostream& bacterium_peaceful::print(std::ostream& out) const
{
	
	out << "reproduction coef = " << m_reproduction_coef << "\n";
	out << "speed coef = " << m_speed_coef << "\n";

	return out;
}
