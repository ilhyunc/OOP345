#include "CheeseParty.h"

#include <string>
#include <iostream>

using namespace std;

namespace sdds {
	CheeseParty::CheeseParty(const CheeseParty& I)
	{*this = I;}

	CheeseParty::CheeseParty(CheeseParty&& I) noexcept
	{*this = move(I);}

	CheeseParty& CheeseParty::operator=(const CheeseParty& other) {
		if (this != &other)	{
			delete[] m_cheeses;
			m_size = other.m_size;
			if (other.m_cheeses) {
				m_cheeses = new const Cheese * [m_size];
				for (size_t i = 0; i < m_size; ++i)
					m_cheeses[i] = other.m_cheeses[i];
			}
		}
		return *this;
	}

	CheeseParty& CheeseParty::operator=(CheeseParty&& other) noexcept {
		if (this != &other) {
			delete[] m_cheeses;
			m_size = other.m_size;
			m_cheeses = other.m_cheeses;				
			other.m_size = 0;
			other.m_cheeses = nullptr;
		}
		return *this;
	}

	CheeseParty::~CheeseParty()
	{delete[] m_cheeses;}

	CheeseParty& CheeseParty::addCheese(const Cheese& cheese){
		bool exist = false;
		if (m_size > 0) {
			for (size_t i = 0; i < m_size; i++)	{
				if (m_cheeses[i] == &cheese) { exist = true;}
			}

			if (!exist) {
				const Cheese** temp = m_cheeses;
				m_cheeses = new const Cheese * [m_size + 1];

				for (size_t i = 0; i < m_size; i++)	{m_cheeses[i] = temp[i];}				
				m_cheeses[m_size] = &cheese;
				m_size++;
				delete[] temp;
			}
		}
		else {
			m_cheeses = new const Cheese * [1];
			m_cheeses[0] = &cheese;
			m_size++;
		}
		return *this;
	}

	CheeseParty& CheeseParty::removeCheese() {
		int exist = -1;
		int index = 0;
		if (m_size > 0) {

			for (size_t i = 0; i < m_size && exist == -1; i++) {
				if (m_cheeses[i]->getWeight() == 0)	{exist = i;}
			}

			if (exist != -1){
				const Cheese** temp = m_cheeses;
				m_cheeses = new const Cheese * [m_size - 1];

				for (int i = 0; i < (int)m_size - 1; i++, index++) {
					if (index == exist) { index++; }
					m_cheeses[i] = temp[index];
				}

				m_size--;
				delete[] temp;
			}
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const CheeseParty& party)
	{
		os << "--------------------------" << endl;
		os << "Cheese Party" << std::endl;
		os << "--------------------------" << endl;
		if (party.m_size > 0)
		{
			for (size_t i = 0; i < party.m_size; ++i)
			{
				os << *party.m_cheeses[i];
			}
		}
		else
		{
			os << "This party is just getting started!" << endl;
		}
		os << "--------------------------" << endl;

		return os;
	}

}