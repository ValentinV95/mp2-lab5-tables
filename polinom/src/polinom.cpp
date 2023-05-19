
#include "../include/polinom.h"



void polinom::push(double data, int xyz)
{
	int flg = 1, flg2 = 1;
	if (head == nullptr)
	{
		push_start(data, xyz);
		flg = 0;
		flg2 = 0;
	}
	else if (head->xyz > xyz)
	{
		push_start(data, xyz);
		flg = 0;
		flg2 = 0;
	}
	else for (auto m_it = head; m_it != nullptr && flg2; m_it = m_it->next)
	{
		if (m_it->xyz == xyz)
		{
			push_add(data, m_it);
			flg = 0;
			flg2 = 0;
		}
		else if (m_it->next != nullptr && m_it->next->xyz > xyz)
		{
			push_between(data, xyz, m_it, m_it->next);
			flg = 0;
			flg2 = 0;
		}
		else if (flg && m_it->next == nullptr)
		{
			push_end(data, xyz, m_it);
			flg = 0;
			flg2 = 0;
		}
	}

}
void polinom::push_start(double data, int xyz)
{
	monom* mon = new monom(data, xyz, head);
	head = mon;
}
void polinom::push_between(double data, int xyz, monom* last, monom* next)
{
	monom* mon = new monom(data, xyz);
	last->next = mon;
	mon->next = next;
}
void polinom::push_end(double data, int xyz, monom* last)
{
	monom* mon = new monom(data, xyz);
	last->next = mon;
	mon->next = nullptr;
}
void polinom::push_add(double data, monom* itis)
{
	itis->data += data;
}


//----------------[ Перегрузка операций ]----------------------



polinom polinom::operator+(const polinom& second)
{
	polinom p_tmp;
	/*
	for (auto m_it = this->head; m_it != nullptr; m_it = m_it->next)
	{
		p_tmp.push(this->head->data, this->head->xyz);
	}
	for (auto m_it_2 = second.head; m_it_2 != nullptr; m_it_2 = m_it_2->next)
	{
		p_tmp.push(second.head->data, second.head->xyz);
	}
	*/
	auto m_it_1 = head, m_it_2 = second.head;
	while (m_it_1 != nullptr || m_it_2 != nullptr)
	{
		if (m_it_1 == nullptr)
		{
			p_tmp.push(m_it_2->data, m_it_2->xyz);
			m_it_2 = m_it_2->next;
		}
		else if (m_it_2 == nullptr)
		{
			p_tmp.push(m_it_1->data, m_it_1->xyz);
			m_it_1 = m_it_1->next;
		}
		else if (m_it_1->xyz == m_it_2->xyz)
		{
			p_tmp.push(m_it_1->data + m_it_2->data, m_it_1->xyz);
			m_it_1 = m_it_1->next;
			m_it_2 = m_it_2->next;
		}
		else if (m_it_1->xyz > m_it_2->xyz)
		{
			p_tmp.push(m_it_2->data, m_it_2->xyz);
			m_it_2 = m_it_2->next;
		}
		else if (m_it_2->xyz > m_it_1->xyz)
		{
			p_tmp.push(m_it_1->data, m_it_1->xyz);
			m_it_1 = m_it_1->next;
		}
	}
	return p_tmp;
}

polinom polinom::operator-(polinom second)
{
	polinom p_tmp = second * -1.0;
	p_tmp = *this + p_tmp;
	return p_tmp;
}

polinom polinom::operator*(const polinom& second)
{
	polinom p_tmp;
	for (auto m_it = this->head; m_it != nullptr; m_it = m_it->next)
	{
		for (auto m_it_2 = second.head; m_it_2 != nullptr; m_it_2 = m_it_2->next)
		{
			p_tmp.push((m_it->data) * (m_it_2->data), (m_it->xyz) + (m_it_2->xyz));

			if ((m_it->data) * (m_it_2->data) != 0)
			{
				if (((m_it->xyz) % 100 + (m_it_2->xyz) % 100) >= 100)
					throw exception("При умножении полиномов степень z в каком-то мономе стала больше 99");

				if ((((m_it->xyz) - (m_it->xyz) % 10000) + ((m_it_2->xyz) - (m_it_2->xyz) % 10000)) / 10000 >= 100)
					throw exception("При умножении полиномов степень x в каком-то мономе стала больше 99");

				if ((((m_it->xyz) % 10000 - (m_it->xyz) % 100) + ((m_it_2->xyz) % 10000 - (m_it_2->xyz) % 100)) / 100 >= 100)
					throw exception("При умножении полиномов степень y в каком-то мономе стала больше 99");
			}
		}
	}
	return p_tmp;
}

polinom polinom::operator*(const double& var)
{
	polinom tmp;
	for (auto m_it = this->head; m_it != nullptr; m_it = m_it->next)
	{
		tmp.push(m_it->data * var, m_it->xyz);
	}
	return tmp;
}











void polinom::clear()
{
	if (head != nullptr)
	{
		auto it1 = head;
		for (auto it = head->next; it != nullptr; it = it->next)
		{
			delete[]it1;
			it1 = it;
		}
		delete[]it1;
	}
	head = nullptr;
}



bool polinom::operator ==(const polinom& second) const noexcept
{
	auto m_it_1 = head, m_it_2 = second.head;
	while (m_it_1 != nullptr && m_it_2 != nullptr)
	{
		if (m_it_1->data != m_it_2->data || m_it_1->xyz != m_it_2->xyz)
		{
			return false;
		}
	}
	if (m_it_1 != nullptr) return false;
	else if (m_it_2 != nullptr) return false;
	return true;
}
bool polinom::operator!=(const polinom& second) const noexcept
{
	return !(*this == second);
}