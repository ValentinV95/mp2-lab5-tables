#include "pair.hpp"
#include "polynomial.h"

template<>
void Pair<int>::getPair()
{
	std::cout << "|" << key;
	for (size_t i = 0; i < (24 - key.size()); i++)
		std::cout << " ";
	std::cout << "| ";
	std::cout << data << std::endl;
	for (size_t i = 0; i < (1 + 4 + 20 + 1); i++)
		std::cout << "-";
	std::cout << std::endl;
}

template <>
void Pair<Polynomial>::getPair()
{
	std::cout << "|" << key;
	for (size_t i = 0; i < (24 - key.size()); i++)
		std::cout << " ";
	std::cout << "| ";
	data.getPolynomial();
	for (size_t i = 0; i < (1 + 4 + 20 + 1); i++)
		std::cout << "-";
	std::cout << std::endl;
}