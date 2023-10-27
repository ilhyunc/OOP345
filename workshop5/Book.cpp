#include "Book.h"

#include <iomanip>

using namespace std;
namespace sdds {
	void booksTrim(string& str) 
	{
		size_t start = str.find_first_not_of(' '); //여백이 아닌 첫 문자열이 시작되는 index
		size_t end = str.find_last_not_of(' '); //여백이 아닌 마지막 문자열이 끝나는 index
		str = str.substr(start, end - start + 1);// +1없으면 마지막 자리 문자 출력안됨.
	}

	const std::string& Book::title() const
	{
		return m_title;
	}

	const std::string& Book::country() const
	{
		return m_country;
	}

	const size_t& Book::year() const
	{
		return m_year;
	}

	double& Book::price()
	{
		return m_price;
	}

	Book::Book(const std::string& strBook)
	{
		std::string temp = strBook;
		std::string author = temp.substr(0, temp.find(','));
		booksTrim(author);
		temp.erase(0, temp.find(',') + 1);

		std::string title = temp.substr(0, temp.find(','));
		booksTrim(title);
		temp.erase(0, temp.find(',') + 1);

		std::string country = temp.substr(0, temp.find(','));
		booksTrim(country);
		temp.erase(0, temp.find(',') + 1);

		double price = std::stod(temp);
		temp.erase(0, temp.find(',') + 1);

		int year = std::stoi(temp);
		temp.erase(0, temp.find(',') + 1);

		std::string desc = temp;
		booksTrim(desc);

		m_author = author;
		m_title = title;
		m_country = country;
		m_year = year;
		m_price = price;
		m_desc = desc;
	}

	std::ostream& operator<<(std::ostream& os, const Book& book)
	{
		os << setw(20) << right << book.m_author << " | ";
		os << setw(22) << right << book.m_title << " | ";
		os << setw(5) << right << book.m_country << " | ";
		os << setw(4) << right << book.m_year << " | ";
		os << setw(6) << fixed << setprecision(2) << right << book.m_price << " | ";
		os << book.m_desc << endl;

		return os;
	}
}