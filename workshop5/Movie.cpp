#include "Movie.h"

#include <iomanip>
#include <string>//  std::stoi,  std::stod

using namespace std;

namespace sdds {
	void moviesTrim(std::string& src)
	{
		size_t begin = src.find_first_not_of(' ');
		size_t end = src.find_last_not_of(' ');
		src = src.substr(begin, end - begin + 1);
	}

	const std::string& Movie::title() const
	{
		return m_title;
	}

	Movie::Movie(const std::string& strMovie)
	{
		std::string temp = strMovie;

		std::string title = temp.substr(0, temp.find(','));
		moviesTrim(title);
		temp.erase(0, temp.find(',') + 1);

		int year = std::stoi(temp);
		temp.erase(0, temp.find(',') + 1);

		std::string desc = temp;
		moviesTrim(desc);
		m_title = title;
		m_year = year;
		m_desc = desc;
	}

	std::ostream& operator<<(std::ostream& os, const Movie& movie)
	{
		os << std::setw(40) << std::right << movie.m_title << " | ";
		os << std::setw(4) << std::right << movie.m_year << " | ";
		os << movie.m_desc << std::endl;

		return os;
	}



}