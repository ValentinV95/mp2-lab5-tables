#include "../include/Polinom.h"

void Polinom::push(double nk, int nxyz)
{
	Monom* N = new Monom();
	if (head == nullptr || head->xyz > nxyz)
	{

		N->xyz = nxyz;
		N->k = nk;
		N->next = head;
		head = N;
	}
	else
	{
		bool flg = 1;

		for (auto it = head; it != nullptr; it = it->next)
		{
			if (it->xyz == nxyz)
			{
				flg = 0;
				it->k += nk;
				break;
			}

			if (it->next != nullptr)
			{
				if (it->next->xyz > nxyz)
				{
					N->xyz = nxyz;
					N->k = nk;
					N->next = it->next;
					it->next = N;
					flg = 0;
					break;
				}

				if ((it->next->xyz == nxyz) && (fabs(it->next->k + nk) < 0.00000000000000001))
				{
					auto itd = it->next;
					it->next = it->next->next;
					delete[]itd;
					break;
				}

			}
			if (flg && it->next == nullptr)
			{
				N->xyz = nxyz;
				N->k = nk;
				N->next = nullptr;
				it->next = N;
				break;
			}
		}

	}
}

Polinom& Polinom::operator=(Polinom second)
{
	for (auto it = head, it2 = head; it != nullptr;)
	{
		it = it->next;
		delete[]it2;
		it2 = it;
	}
	head = nullptr;
	for (auto it = second.head; it != nullptr; it = it->next)
	{
		push(it->k, it->xyz);
	}
	return *this;
}

Polinom Polinom::operator+(Polinom second)
{
	Polinom A;
	for (auto it1 = head, it2 = second.head; it1 != nullptr || it2 != nullptr;)
	{
		if (it1 == nullptr)
		{
			A.push(it2->k, it2->xyz);
			it2 = it2->next;
			continue;
		}
		else if (it2 == nullptr)
		{
			A.push(it1->k, it1->xyz);
			it1 = it1->next;
			continue;
		}
		else
		{
			if (it1->xyz > it2->xyz)
			{
				A.push(it2->k, it2->xyz);
				it2 = it2->next;
			}
			else if (it1->xyz < it2->xyz)
			{
				A.push(it1->k, it1->xyz);
				it1 = it1->next;
			}
			else if (it1->xyz == it2->xyz)
			{
				A.push(it1->k + it2->k, it1->xyz);
				it2 = it2->next;
				it1 = it1->next;
			}
		}
	}
	return A;
}

Polinom Polinom::operator-(Polinom second)
{
	Polinom B;
	for (auto it = second.head; it != nullptr; it = it->next)
	{
		B.push(it->k * (-1), it->xyz);
	}
	return *this + B;
}

Polinom Polinom::operator*(double cont)
{
	Polinom C;
	for (auto it = head; it != nullptr; it = it->next)
	{
		C.push(it->k * cont, it->xyz);
	}
	return C;
}

Polinom Polinom::operator*(Polinom second)
{
	Polinom A;
	for (auto it1 = head; it1 != nullptr; it1 = it1->next)
		for (auto it2 = second.head; it2 != nullptr; it2 = it2->next)
		{
			if (it1->xyz + it2->xyz >= 1000 || it1->xyz % 100 + it2->xyz % 100 >= 100 || it1->xyz % 10 + it2->xyz % 10 >= 10) throw invalid_argument("Over limit of stepen");
			A.push(it1->k * it2->k, it1->xyz + it2->xyz);
		}
	return A;
}

void Polinom::show_polinom()
{
	int x, y, z;
	for (auto it = head; it != nullptr; it = it->next)
	{
		if (fabs(it->k) > 0.00000000000000001)
		{
			x = it->xyz / 100;
			y = (it->xyz % 100 - it->xyz % 10) / 10;
			z = it->xyz % 10;
			if (it->k > 0 && it != head) cout << "+ ";
			cout << it->k;
			if (x > 0)
			{
				cout << "*x";
				if (x > 1)
					cout << "^" << x;
			}
			if (y > 0)
			{
				cout << "*y";
				if (y > 1)
					cout << "^" << y;
			}
			if (z > 0)
			{
				cout << "*z";
				if (z > 1)
					cout << "^" << z;
			}
			cout << " ";
		}
	}
}

double Polinom::solve(double x, double y, double z)
{
	double res = 0.0;
	for (auto it = head; it != nullptr; it = it->next)
	{
		res += it->k * pow(x, it->xyz / 100) * pow(y, (it->xyz % 100) / 10) * pow(z, it->xyz % 10);
	}
	return res;
}

void Polinom::string_to_polinom(string polim)
{
	double str;
	int nxyz, ic;
	string dbl;
	int tmp, tmp2;
	bool flg1 = 1, flg2 = 1, flg3 = 1;
	for (int i = 0; i < polim.size(); i++)
	{
		flg1 = 1, flg2 = 1, flg3 = 1;
		dbl = "";
		str = 1.0;
		if (i + 1 < polim.size())
			if (polim[i] == '-')
			{
				str = -1.0;
				i++;
			}
		nxyz = 0;
		tmp = int(polim[i]);

		if (tmp >= 48 && tmp < 57 || tmp == '.' || tmp == '-')
		{
			ic = 0;
			while (tmp >= 48 && tmp < 57 || tmp == '.' || tmp == '+' || tmp == '-' || tmp == 'e' || tmp == '.')
			{
				if (ic != 0 && (tmp == '+' || tmp == '-')) break;
				if (i == 0 && tmp == '+' || tmp == 'e') throw invalid_argument("Bad input");

				if (flg1 && flg2 && flg3 && tmp == '.')
				{
					flg1 = 0;
					dbl += polim[i];
					i++;
					continue;
				}
				if (!flg1 && flg2 && flg3 && tmp == 'e' && (i + 1) < polim.size())
				{
					flg2 = 0;
					dbl += polim[i];
					dbl += polim[i + 1];
					i += 2;
					continue;
				}
				if (!flg1 && !flg2 && flg3 && tmp == 'y' || tmp == 'x' || tmp == 'z' || tmp == '-' || tmp == '+')
				{
					flg3 = 0;
					continue;
				}
				dbl += polim[i];
				i++;
				tmp = int(polim[i]);
				ic++;
			}
			str = str * string_to_double(dbl);
		}
		if (polim[i] == 'x')
		{
			if (i + 2 < polim.size())
			{
				if (polim[i + 1] == '^' && int(polim[i + 2]) - 48 < 10 && int(polim[i + 2]) - 48 > -1)
				{
					nxyz += 100 * (int(polim[i + 2]) - 48) - 100;
					i += 2;
				}
			}
			nxyz += 100;
			i++;
		}
		if (polim[i] == 'y')
		{
			if (i + 2 < polim.size())
			{
				if (polim[i + 1] == '^' && int(polim[i + 2]) - 48 < 10 && int(polim[i + 2]) - 48 > -1)
				{
					nxyz += 10 * (int(polim[i + 2]) - 48) - 10;
					i += 2;
				}
			}
			nxyz += 10;
			i++;
		}
		if (polim[i] == 'z')
		{
			if (i + 2 < polim.size())
			{
				if (polim[i + 1] == '^' && int(polim[i + 2]) - 48 < 10 && int(polim[i + 2]) - 48 > -1)
				{
					nxyz += 1 * (int(polim[i + 2]) - 48) - 1;
					i += 2;
				}
			}
			nxyz += 1;
			i++;
		}
		if (polim[i] == '+')
		{
			push(str, nxyz);
			continue;
		}
		if (polim[i] == '-')
		{
			push(str, nxyz);
			i--;
			continue;
		}
		if (i == polim.size())
		{
			push(str, nxyz);
		}

	}
}

std::ostream& Polinom::operator<< (std::ostream& out)
{
	out << "";
	show_polinom();
	return out;
}

Polinom::~Polinom()
{
/*	if (head != nullptr)
	{
		auto it_tmp = head;
		for (auto it = head->next; it != nullptr; it = it->next)   // Ќикак не получаетс€ построить деструктор, который не будет удал€ть локальную пам€ть
		{                                                         //  в операторах + и -, там создаетс€ новый объект в который все записываетс€, но по окончанию
			delete[]it_tmp;                                      //   оператора у него вызываетс€ деструктор и все мономы у него стираютс€, дела€ эти операторы
			it_tmp = it;                                        //    бесполезными. ѕросьба объ€снить как обойти такую проблему.
		}
		delete[]it_tmp;
	}
*/
}

double string_to_double(string s)
{
	int i, LEN, flg = 1, kd = 0, ks = 0, z;
	double res = 0.0, Help = 10.0, znak = 0.0;

	LEN = s.length();

	for (i = 0; i < LEN; i++)
	{
		if ((int(s[i]) < 48 || int(s[i]) > 57) && (s[i] != '-') && (s[i] != '+') && (s[i] != 'e') && (s[i] != '.')) throw  invalid_argument("This is not double!");
		if ((flg) && (s[i] != '.') && (s[i] != 'e'))
		{
			res *= Help;
			res += (int(s[i]) - 48);

		}
		if (s[i] == '.')
		{
			kd++;
			flg = 0;
			Help = 1.0 / 10.0;
			if (kd > 1) throw  invalid_argument("Two dots!");
		}
		if (s[i] == 'e')
		{
			if (i + 1 == LEN) throw invalid_argument("Bad form of double!");
			i++;
			Help = 10.0;
			while (i < LEN)
			{
				if ((int(s[i]) < 48 && int(s[i]) > 57) && (s[i] != '-') && (s[i] != '+') && (s[i] != 'e')) throw  invalid_argument("This is not double!");
				if ((s[i] == 'e') || (s[i] == '.')) throw invalid_argument("Bad input!Dot after 'e' or 'e' after 'e'");
				else if (s[i] == '-')
				{
					ks++;
					z = -1;
					if (ks > 1) throw invalid_argument("Bad input!Two symbols of plus or substract!");
				}
				else if (s[i] == '+')
				{
					ks++;
					z = 1;
					if (ks > 1) throw invalid_argument("Bad input!Two symbols of plus or substract!");
				}
				else
				{

					znak *= Help;
					znak += int(s[i]) - 48;

				}
				i++;
			}
			res *= pow(10, z * znak);
			flg = 1;

		}
		if (flg == 0 && s[i] != '.')
		{
			res += (int(s[i]) - 48) * Help;
			Help /= 10.0;
		}



	}

	return res;
}