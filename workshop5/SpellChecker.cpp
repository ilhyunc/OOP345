#include "SpellChecker.h"

#include <fstream>
#include <iomanip>

using namespace std;

namespace sdds {

	SpellChecker::SpellChecker(const char* filename){
		ifstream file(filename);
		if (file) {
			for (size_t i = 0; i < 6; i++) {
				file >> m_badWords[i]; //공백무시하고 단어만 읽음.
				file >> m_goodWords[i]; //공백무시하고 단어만 읽음.
			}
		}
		else //exception, throw = try, catch 사용, throw하는 타입에 따라 catch의 argument가 정해짐
		{ throw "Bad file name!"; }
	}

	void SpellChecker::operator()(std::string& text)
	{
		for (size_t i = 0; i < 6; i++) 
		{
			size_t index;
			while ((index = text.find(m_badWords[i])) != string::npos)// badWord가 있는동안 while loop
			{
				text.replace(index, m_badWords[i].length(), m_goodWords[i]); //m_badWords의 첫 index부터, 단어의 길이까지, m_goodWords로 변경
				m_replaceCount[i]++;
			}
		}
	}
	void SpellChecker::showStatistics(std::ostream& out) const
	{
		out << "Spellchecker Statistics" << endl;
		for (size_t i = 0; i < 6 && m_badWords[i].length() != 0; i++) {
			out << setw(15) << right << m_badWords[i] << ": " << m_replaceCount[i] << " replacements" << endl;
		}
	}
}