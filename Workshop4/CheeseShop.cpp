#include "CheeseShop.h"

#include <string>
#include <iostream>

using namespace std;

namespace sdds {
	CheeseShop::~CheeseShop()
	{
		for (size_t i = 0; i < m_size; i++) 
		{
			delete m_cheeses[i];
		}

		delete[] m_cheeses;
	}

	CheeseShop::CheeseShop(const CheeseShop& I) 
	{
		*this = I;
	}

	CheeseShop& CheeseShop::operator=(const CheeseShop& other)
	{
		if (this != &other) 
		{
			for (size_t i = 0; i < m_size; ++i) 
			{
				delete m_cheeses[i];
			}
			delete[] m_cheeses;

			m_shopName = other.m_shopName;
			m_size = other.m_size;
			if (other.m_cheeses)
			{
				m_cheeses = new Cheese * [m_size];
				for (size_t i = 0; i < m_size; ++i) 
				{
					m_cheeses[i] = new Cheese(*(other.m_cheeses[i]));
				}
			}
			else
			{
				m_cheeses = nullptr;
			}
		}

		return *this;
	}

	CheeseShop::CheeseShop(CheeseShop&& I) noexcept
	{
		*this = move(I);
	}

	CheeseShop& CheeseShop::operator=(CheeseShop&& other) noexcept
	{
		if (this != &other)
		{
			for (size_t i = 0; i < m_size; ++i) 
			{
				delete m_cheeses[i];
			}
			delete[] m_cheeses;

			m_shopName = move(other.m_shopName);
			m_size = other.m_size;
			m_cheeses = other.m_cheeses;

			other.m_size = 0;
			other.m_cheeses = nullptr;
		}
		return *this;
	}

	CheeseShop& CheeseShop::addCheese(const Cheese& cheese)
	{
		Cheese** temp = new Cheese * [m_size + 1];
		for (size_t i = 0; i < m_size; ++i) 
		{
			temp[i] = m_cheeses[i];
		}
		temp[m_size] = new Cheese(cheese);
		delete[] m_cheeses;
		m_cheeses = temp;
		m_size++;
		return *this;
	}
	
	std::ostream& operator<<(std::ostream& os, const CheeseShop& shop)
	{
		os << "--------------------------" << endl;
		os << shop.m_shopName << endl;
		os << "--------------------------\n";
		if (shop.m_size == 0)
		{
			os << "This shop is out of cheese!" << endl;
		}
		else 
		{
			for (size_t i = 0; i < shop.m_size; ++i)
			{
				os << *(shop.m_cheeses[i]);
			}
		}
		os << "--------------------------" << endl;
		return os;
	}

}
