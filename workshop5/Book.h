#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream>
#include <string>

namespace sdds {
	class Book {
		std::string m_author{};
		std::string m_title{};
		std::string m_country{};
		size_t m_year{};
		double m_price{};
		std::string m_desc{};
	public:
		Book() {}
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price(); // 원본을 쓰기위해 const 사용 X 람다 표현식에서 사용.
		Book(const std::string& strBook);

		template<typename T>//함수만 템플릿
		void fixSpelling(T& spellChecker) 
		{
			spellChecker(m_desc); //functor 함수처럼 사용
		}

		friend std::ostream& operator<<(std::ostream& os, const Book& book);
	};
}

#endif