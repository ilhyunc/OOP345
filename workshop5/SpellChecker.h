#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

#include <iostream>

namespace sdds {
	class SpellChecker {
		std::string m_badWords[6]{}; //string ��ü�� array�̴� .
		std::string m_goodWords[6]{};

		size_t m_replaceCount[6]{};
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);//functor �Լ�ó�� ��������
		void showStatistics(std::ostream& out) const;
	};
}

#endif