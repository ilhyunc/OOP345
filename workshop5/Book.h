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
		double& price(); // ������ �������� const ��� X ���� ǥ���Ŀ��� ���.
		Book(const std::string& strBook);

		template<typename T>//�Լ��� ���ø�
		void fixSpelling(T& spellChecker) 
		{
			spellChecker(m_desc); //functor �Լ�ó�� ���
		}

		friend std::ostream& operator<<(std::ostream& os, const Book& book);
	};
}

#endif