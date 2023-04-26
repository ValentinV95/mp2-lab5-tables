#include "polynomial.h"

// Polynomial
Polynomial::Polynomial()
{}

Polynomial::Polynomial(const Polynomial& other) : tData(other.tData)
{}

Polynomial::Polynomial(const List<Monom>& other)
{
	if (other.isEmpty());

	else this->tData = other;
}

Polynomial::Polynomial(const Monom& monom)
{
	this->tData.push(monom);
}

void Polynomial::truePolynomial()
{
	if (tData.isEmpty()) return;
	Node<Monom>* temp = tData.begin();

	while (temp->next)
	{
		if (temp->data.degree == temp->next->data.degree)
		{
			temp->data += temp->next->data;
			tData.deleteNode(temp->next);
		}

		else
		{
			temp = temp->next;
		}
	}

	temp = tData.begin();

	while (temp)
	{
		if (fabs(temp->data.coef) < 1e-15)
		{
			Node<Monom>* cont = temp;
			temp = temp->next;
			tData.deleteNode(cont);
		}

		else
		{
			temp = temp->next;
		}
	}
}

void Polynomial::setPolynomial()
{
	if (!tData.isEmpty()) tData.clear();

	size_t degree;
	int size;
	double coef;

	cout << "Введите количество мономов в полиноме: ";
	cin >> size;
	if (size < 0)
	{
		string error = "\"Polynomial::setPolynomial\": min size is 0,\n";
		error += " but it's " + to_string(size);
		throw error;
	}

	for (size_t i = 0; i < size; i++)
	{
		cout << "Моном " << (i + 1) << endl;
		cout << "Введите степень монома: ";
		cin >> degree;

		cout << "Введите коэффициент монома: ";
		cin >> coef;

		if (fabs(coef) < 1e-15) continue;
		tData.push(Monom(degree, coef));
	}

	this->truePolynomial();
}

void Polynomial::getPolynomial()
{
	if (tData.isEmpty()) cout << "0";

	else
	{
		Node<Monom>* temp = tData.begin();

		for (size_t i = 0; i < tData.size(); i++, temp = temp->next)
		{
			if ((i != 0) && temp->data.coef > 0) cout << " + ";
			cout << temp->data.stringMonom();
		}
	}

	cout << endl;
}

const Polynomial& Polynomial::operator =(const Polynomial& other)
{
	this->tData = other.tData;

	return *this;
}

Polynomial Polynomial::operator +(const Polynomial& other) const
{
	Polynomial third(*this);

	third.tData.merge(other.tData);
	third.truePolynomial();

	return third;
}

Polynomial Polynomial::operator *(const Monom& monom) const
{
	Polynomial third(*this);
	Node<Monom>* temp = third.tData.begin();

	while (temp)
	{
		temp->data *= monom;
		temp = temp->next;
	}

	third.truePolynomial();

	return third;
}

Polynomial Polynomial::operator *(double var) const
{
	Polynomial third(*this);
	
	Node<Monom>* temp = third.tData.begin();

	while (temp)
	{
		temp->data *= var;
		temp = temp->next;
	}

	third.truePolynomial();

	return third;
}

Polynomial Polynomial::operator -(const Polynomial& other) const
{
	Polynomial third(*this);
	third.tData.merge((other * -1.0).tData);
	third.truePolynomial();

	return third;
}

Polynomial Polynomial::operator *(const Polynomial& other) const
{
	Polynomial third(*this);
	Polynomial fourth;
	Node<Monom>* temp = other.tData.begin();

	while (temp)
	{
		fourth = fourth + third * temp->data;
		temp = temp->next;
	}

	third = fourth;

	third.truePolynomial();

	return third;
}