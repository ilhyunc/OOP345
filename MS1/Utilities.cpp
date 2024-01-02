#include "Utilities.h"

using namespace std;
namespace sdds {
	char Utilities::m_delimiter{};

	void trim(string& string) 
	{
		if (string.length() > 0)
		{
			size_t begin = string.find_first_not_of(' ');
			size_t end = string.find_last_not_of(' ');
			if (begin < 0)
			{
				string = "";
			}
			else 
			{
				string = string.substr(begin, end - begin + 1);
			}
		}
	}

	void Utilities::setFieldWidth(size_t newWidth) 
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		int nextTokenPos;
		string temp;
		string string = str.substr(next_pos);

		if (str[next_pos] == m_delimiter || next_pos >= str.length()) 
		{
			more = false;
			throw invalid_argument("Delimiter is found!");
		}
		else 
		{
			if ((nextTokenPos = string.find_first_of(m_delimiter)) != EOF)
			{
				temp = string.substr(0, nextTokenPos);
				trim(temp);
				next_pos += (nextTokenPos + 1);
				more = true;
			}
			else
			{
				temp = string;
				trim(temp);
				more = false;
			}
		}

		if (m_widthField < temp.length())
		{
			setFieldWidth(temp.length());
		}

		return temp;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}