#include "SpellChecker.h"

#include <fstream>
#include <iomanip>

using namespace std;

namespace sdds {

	SpellChecker::SpellChecker(const char* filename){
		ifstream file(filename);
		if (file) {
			for (size_t i = 0; i < 6; i++) {
				file >> m_badWords[i]; //���鹫���ϰ� �ܾ ����.
				file >> m_goodWords[i]; //���鹫���ϰ� �ܾ ����.
			}
		}
		else //exception, throw = try, catch ���, throw�ϴ� Ÿ�Կ� ���� catch�� argument�� ������
		{ throw "Bad file name!"; }
	}

	void SpellChecker::operator()(std::string& text)
	{
		for (size_t i = 0; i < 6; i++) 
		{
			size_t index;
			while ((index = text.find(m_badWords[i])) != string::npos)// badWord�� �ִµ��� while loop
			{
				text.replace(index, m_badWords[i].length(), m_goodWords[i]); //m_badWords�� ù index����, �ܾ��� ���̱���, m_goodWords�� ����
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