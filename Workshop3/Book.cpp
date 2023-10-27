#include "Book.h"

#include <iomanip>

using namespace std;

namespace sdds {
	bool Book::operator<(const Book& other) const
	{
		return (double)m_numPages / m_numChapters < (double)other.m_numPages / other.m_numChapters;
	}

	bool Book::operator>(const Book& other) const
	{
		return (double)m_numPages / m_numChapters > (double)other.m_numPages / other.m_numChapters;
	}

	ostream& Book::print(ostream& os) const
	{
		if (!m_title.empty())
		{
			if (m_title[0] == 'S')
			{
				os << right << setw(50) << m_title;
			}
			else
			{
				os << right << setw(49) << m_title;
			}

			os << "," << m_numChapters << "," << m_numPages << " | " << "(" << fixed << setprecision(6) << (double)m_numPages / m_numChapters << setprecision(1) << ")    ";
		}
		else
		{
			os << "| Invalid book data";//
		}

		return os;
	}


	ostream& operator<<(ostream& os, const Book& bk)
	{
		return bk.print(os);
	}

};