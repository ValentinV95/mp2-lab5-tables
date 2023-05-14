#pragma once

#include <iostream>
#include <exception>
#include<Windows.h>

using namespace std;

struct monom
{
	double data;
	int xyz;
	monom* next;

	monom(double m_data, int m_xyz, monom* m_next)
	{
		data = m_data;
		xyz = m_xyz;
		next = m_next;
	}


	monom(double m_data, int m_xyz)
	{
		data = m_data;
		xyz = m_xyz;
	}
};
