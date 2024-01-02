#include "Station.h"
#include "Utilities.h"

using namespace std;
namespace sdds {
	size_t Station::m_widthField{};
	size_t Station::id_generator{};

	Station::Station(const std::string& record)
	{
		Utilities utility;
		size_t nextPos = 0;
		bool more = true;

		m_itemName = utility.extractToken(record, nextPos, more);
		m_nextSN = stoi(utility.extractToken(record, nextPos, more));
		m_numOfStockItem = stoi(utility.extractToken(record, nextPos, more));

		if (utility.getFieldWidth() > Station::m_widthField) 
		{
			Station::m_widthField = utility.getFieldWidth();
		}

		m_stationDes = utility.extractToken(record, nextPos, more);
		m_stationID = ++id_generator;
	}

	const std::string& Station::getItemName() const
	{
		return m_itemName;
	}

	size_t Station::getNextSerialNumber() 
	{
		return m_nextSN++;
	}

	size_t Station::getQuantity() const
	{
		return m_numOfStockItem;
	}

	void Station::updateQuantity()
	{
		if (m_numOfStockItem > 0)
		{
			m_numOfStockItem--;
		}
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << right << setw(3) << setfill('0') << m_stationID << " | " << left << setw(m_widthField) << setfill(' ') << m_itemName
			<< " | " << right << setw(6) << setfill('0') << m_nextSN << " | ";
		if (full) 
		{
			os << right << setw(4) << setfill(' ') << m_numOfStockItem << " | " << m_stationDes;
		}

		os << endl;
	}

}