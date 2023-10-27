#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H

#include <iostream>

namespace sdds {
	class SpellChecker {
		std::string m_badWords[6]{}; //string 자체가 array이다 .
		std::string m_goodWords[6]{};

		size_t m_replaceCount[6]{};
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);//functor 함수처럼 쓰기위해
		void showStatistics(std::ostream& out) const;
	};
}

#endif