#include <vector>

#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;
namespace sdds {

	size_t CustomerOrder::m_widthField{};

	CustomerOrder::CustomerOrder(const std::string& token) 
	{
		size_t nextPos = 0;
		bool more = true;
		Utilities utility;
		vector<Item*> temp;

		m_name = utility.extractToken(token, nextPos, more);
		m_product = utility.extractToken(token, nextPos, more);

		while (more) 
		{
			temp.push_back(new Item(utility.extractToken(token, nextPos, more)));
		}
		m_cntItem = temp.size();
		m_lstItem = new Item * [m_cntItem];

		for (size_t i = 0; i < m_cntItem; i++) 
		{
			m_lstItem[i] = temp[i];
		}

		if (utility.getFieldWidth() > m_widthField)
		{
			m_widthField = utility.getFieldWidth();
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src) 
	{
		throw string("Copy Constructor is not available");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept 
	{
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept 
	{
		if (this != &src) 
		{
			for (size_t i = 0; i < m_cntItem; i++) 
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;
			m_lstItem = src.m_lstItem;
			src.m_lstItem = nullptr;
			src.m_cntItem = 0;
			src.m_name = "";
			src.m_product = "";
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem != 0) 
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool result = true;

		for (size_t i = 0; i < m_cntItem; i++) 
		{
			if (!m_lstItem[i]->m_isFilled) 
			{
				result = false;
			}
		}
		return result;
	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		bool result = true;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) 
			{
				result = false;
			}
		}

		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) 
	{
		bool filled = false;

		for (size_t i = 0; i < m_cntItem; i++) 
		{
			if (m_lstItem[i]->m_isFilled == filled && m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() >= 1) 
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << setw(11) << right;
					os << "Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					filled = true;
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const 
	{
		os << m_name << " - " << m_product << endl;

		for (size_t i = 0; i < m_cntItem; i++) 
		{
			os << std::right;
			os << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << setfill(' ') << left;
			os << setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
			os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
			os << endl;
		}
	}



}