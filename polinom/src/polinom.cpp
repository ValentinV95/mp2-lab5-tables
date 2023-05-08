#include "polinom.h"
#include "Logger.hpp"

double Monom::GetNum(std::string num)
{
	double res = 0.0;
	int step = num.length() - 1;

	for (int i = 0; i < num.length(); i++)
	{
		res += (((int)num[i]) - 48) * pow(10, step--);
	}

	return res;
}

double Monom::StrToNum(std::string str)
{
	int dot = 0, exp = str.size(), step = 0, i = 0;
	double res = 0.0, sign = 1;

	while (exp == str.size() && i < str.size())
	{
		if (str[i] == DELIMITER && !dot && i != 0)
		{
			dot = i;
		}
		else if (str[i] == 'e')
		{
			exp = i;
			if ((((int)str.size()) - exp) < 2 && (str[exp + 1] != '-' || str[exp + 1] != '+'))
				throw std::exception("Incorrect num format");
			if (str[exp + 1] == '-')
				sign = -1;
		}
		else if (str[i] > '9' || str[i] < '0')
			if (dot || i == 0)
				throw std::exception("To much '.' in number, or number starts with '.'");
			else
				throw std::exception("Num string contains invalid charakters");

		i++;
	}

	if (exp != str.size() && str[exp + 1] != '-' && str[exp + 1] != '+')
		throw std::exception("Incorrect num format");

	if (dot)
		res += GetNum(str.substr(0, dot)) + GetNum(str.substr(dot + 1, str.length() - exp - 2)) * pow(10, -(exp - dot - 1));
	else
		res += GetNum(str.substr(0, exp));

	if (exp != str.length())
		return res * pow(10, sign * StrToNum(str.substr(exp + 2, str.length() - exp - 2)));

	return 	res;
}

Monom::Monom()
{
	a = 0.0;
	xyzPow = 9999999;
}

Monom::Monom(double a, uint xPow, uint yPow, uint zPow)
{
	if (xPow > MaxPow || yPow > MaxPow || zPow > MaxPow || xPow < 0 || yPow < 0 || zPow < 0)
		throw std::invalid_argument("Pow of monom was greater then max available (" + std::to_string(MaxPow) + ") or less 0");

	this->a = a;
	this->xyzPow = xPow * 100 + yPow * 10 + zPow;
}

//Ожидаемый формат: a*x^xPow*y^yPow*z^zPow
//xPow,yPow,zPow - просто числа
Monom::Monom(std::string monomStr)
{
	std::string tmp;
	std::vector<std::string> vStr;

	for (int i = 0; i < monomStr.size(); i++)
	{
		if (monomStr[i] == '*')
		{
			vStr.push_back(tmp);
			tmp = "";
		}
		else
		{
			tmp += monomStr[i];
		}
	}

	if (tmp == "")
		throw std::invalid_argument("The input string had an incorrect format, there was a multiplication sign at the end of the string, or the string was empty");

	vStr.push_back(tmp);

	double a = 0.0;
	int xPow = 0, yPow = 0, zPow = 0;

	for (int i = 0; i < vStr.size(); i++)
	{
		switch (vStr[i][0])
		{
		case('x'):
			if (vStr[i][1] != '^' || vStr[i].size() <= 2 || vStr[i].size() > 3) throw std::invalid_argument("Incorrect monom format near x variable");
			xPow = StrToNum(std::string(1, vStr[i][2]));
			break;
		case('y'):
			if (vStr[i][1] != '^' || vStr[i].size() <= 2 || vStr[i].size() > 3) throw std::invalid_argument("Incorrect monom format near y variable");
			yPow = StrToNum(std::string(1, vStr[i][2]));
			break;
		case('z'):
			if (vStr[i][1] != '^' || vStr[i].size() <= 2 || vStr[i].size() > 3) throw std::invalid_argument("Incorrect monom format near z variable");
			zPow = StrToNum(std::string(1, vStr[i][2]));
			break;
		default:
			if (vStr[i][0] == '-')
				a = (-1.0) * StrToNum(vStr[i].substr(1, vStr[i].size()));
			else
				a = StrToNum(vStr[i]);
			break;
		}
	}

	*this = Monom(a, xPow, yPow, zPow);
}

//1 - больше/равно 0, 0 - меньше 0
bool Monom::GetSign() { return a >= 0.0; }

float Monom::GetA() { return a; }

int Monom::GetPow() { return xyzPow; }

bool Monom::IsPowEqual(const Monom& m) { return xyzPow == m.xyzPow; }

std::string Monom::toString() const
{
	std::string monom;
	
	monom += std::to_string(a);

	if ((xyzPow % 1000) / 100 != 0)
		monom += "*x^" + std::to_string((xyzPow % 1000) / 100);

	if ((xyzPow % 100) / 10 != 0)
		monom += "*y^" + std::to_string((xyzPow % 100) / 10);

	if (xyzPow % 10 != 0)
		monom += "*z^" + std::to_string(xyzPow % 10);

	return monom;
}

Monom Monom::operator + (const Monom& other) const
{
	if (this->xyzPow != other.xyzPow)
		throw std::invalid_argument("Pow of monom was not equal");

	return Monom(this->a + other.a, (this->xyzPow % 1000) / 100, (this->xyzPow % 100) / 10, this->xyzPow % 10);
}

Monom Monom::operator - (const Monom& other) const
{
	if (this->xyzPow != other.xyzPow)
		throw std::invalid_argument("Pow of monom was not equal");

	return Monom(this->a - other.a, (this->xyzPow % 1000) / 100, (this->xyzPow % 100) / 10, this->xyzPow % 10);
}

Monom Monom::operator * (const Monom& other)
{
	//I'm very sorry for that
	return Monom(this->a * other.a, ((this->xyzPow % 1000) / 100) + ((other.xyzPow % 1000) / 100), ((this->xyzPow % 100) / 10) + (other.xyzPow % 100) / 10, (this->xyzPow % 10) + (other.xyzPow % 10));
}

Monom Monom::operator * (double a)
{
	return Monom(this->a * a, (this->xyzPow % 1000) / 100, (this->xyzPow % 100) / 10, this->xyzPow % 10);
}

bool Monom::operator > (const Monom& other) const
{
	return this->xyzPow > other.xyzPow;
}

bool Monom::operator < (const Monom& other) const
{
	return this->xyzPow < other.xyzPow;
}

bool Monom::operator == (const Monom& other) const
{
	return this->xyzPow == other.xyzPow && this->a == other.a;
}

std::ostream& operator << (std::ostream& ostr, const Monom& m)
{
	ostr << m.toString();

	return ostr;
}

Polynom::Polynom() {}

Polynom::Polynom(std::string str)
{
	std::string tmp;
	std::vector<std::string> vStr;

	int i = 0;

	while (i < str.size())
	{
		if (str[i] == '+')
		{
			if (tmp.empty())
				throw std::invalid_argument("Incorrect entry string");

			vStr.push_back(tmp);
			tmp = "";
		}
		else if (str[i] == '-')
		{
			if (tmp.empty())
				throw std::invalid_argument("Incorrect entry string");

			vStr.push_back(tmp);
			tmp = "";
			tmp = "-";
		}
		else
		{
			tmp += str[i];
		}

		i++;
	}

	if (tmp != "")
		vStr.push_back(tmp);
	else
		throw std::invalid_argument("Incorrect entry string");

	for (int i = 0; i < vStr.size(); i++)
	{
		bool isMonomUnique = true;
		Monom m(vStr[i]);
		for (auto iter = monoms.begin(); iter != monoms.end() && isMonomUnique; iter++)
		{
			if ((*iter).IsPowEqual(m))
			{
				(*iter) = (*iter) + m;
				isMonomUnique = false;
			}
		}

		if (isMonomUnique)
			monoms.Append(Monom(vStr[i]));
	}
}

Polynom::Polynom(const Polynom& p)
{
	auto iter = p.monoms.begin();

	while (iter != p.monoms.end())
	{
		monoms.Push_Back((*iter));
		iter++;
	}
}

std::string Polynom::toString() const
{
	std::string res = "";

	for (auto iter = monoms.begin(); iter != monoms.end(); iter++)
		res+=(*iter).toString();

	return res;
}

void Polynom::Append(Monom m)
{
	if (m.GetA())
		monoms.Append(m);
}

void Polynom::Push_Back(Monom m)
{
	if (m.GetA())
		monoms.Push_Back(m);
}

Monom Polynom::At(int ind)
{
	return monoms.At(ind);
}

Polynom Polynom::operator + (const Polynom& other) const
{
	Polynom res;

	auto other_iter = other.monoms.begin();
	auto this_iter = monoms.begin();

	while (this_iter != monoms.end() && other_iter != other.monoms.end())
	{
		if ((*this_iter).IsPowEqual(*other_iter))
		{
			res.Push_Back(*this_iter + *other_iter);

			other_iter++;
			this_iter++;
		}
		else if (*this_iter < *other_iter)
		{
			res.Push_Back(*this_iter);
			this_iter++;
		}
		else
		{
			res.Push_Back(*other_iter);
			other_iter++;
		}
	}

	while (this_iter != monoms.end())
	{
		res.Push_Back(*this_iter);
		this_iter++;
	}

	while (other_iter != other.monoms.end())
	{
		res.Push_Back(*other_iter);
		other_iter++;
	}

	return res;
}

Polynom Polynom::operator - (const Polynom& other) const
{
	return *this + other * (-1.0);
}

Polynom Polynom::operator * (double a) const
{
	Polynom res;

	for (auto iter = monoms.begin(); iter != monoms.end(); iter++)
		res.Push_Back((*iter) * a);

	return res;
}

Polynom Polynom::operator * (const Monom& m) const
{
	Polynom res;
	for (auto iter = monoms.begin(); iter != monoms.end(); iter++)
		res.Push_Back((*iter) * m);

	return res;
}

Polynom Polynom::operator * (const Polynom& other) const
{
	Polynom res;

	for (auto iter = monoms.begin(); iter != monoms.end(); iter++)
	{
		Polynom multres = other * (*iter);
		res = res + multres;
	}

	return res;
}

Polynom Polynom::operator = (const Polynom& other)
{
	if (this == &other)
		return *this;

	monoms = other.monoms;

	return *this;
}

bool Polynom::operator == (const Polynom& other) const
{
	bool res = true;

	auto this_iter = monoms.begin();
	auto other_iter = other.monoms.begin();

	while (this_iter != monoms.end() && other_iter != other.monoms.end() && res)
	{
		res = (*this_iter) == (*other_iter);
		this_iter++;
		other_iter++;
	}

	if (this_iter == monoms.end() && other_iter == other.monoms.end())
		return res;
	else
		return false;
}

std::ostream& operator << (std::ostream& ostr, const Polynom& p)
{
	std::string poli;
	if (p.monoms.begin() != p.monoms.end())
	{
		for (auto iter = p.monoms.begin(); iter != p.monoms.end(); iter++)
		{
			if ((*iter).GetSign() && iter != p.monoms.begin()) 
				poli+= "+";

			poli += (*iter).toString();
		}
	}
	else
	{
		ostr << "0.0";
	}

	ostr << poli;

	return ostr;
}

std::istream& operator>>(std::istream& istr, Polynom& p)
{
	std::string input;
	istr >> input;
	p = Polynom(input);
	return istr;
}