#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>
#include <iomanip>

namespace sdds {
	class Station {
		int m_stationID{};
		std::string m_itemName{};
		size_t m_nextSN{};
		size_t m_numOfStockItem{};
		std::string m_stationDes{};

		static size_t m_widthField;// class variable
		static size_t id_generator;// class variable

	public:
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}

#endif