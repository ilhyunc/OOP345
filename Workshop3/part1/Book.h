#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include <iostream> 

namespace sdds {
	class Book
	{
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
	public:
		Book():m_numChapters(1), m_numPages(10000) {};
		Book(const std::string& title, unsigned nChapters, unsigned nPages) : m_title{ title }, m_numChapters{ nChapters }, m_numPages{ nPages } {};

		// TODO: In completing Part 1, add here the missing Q
		// member prototypes that would be necessary for the 
		// Collection module code and tester module w3_p1.cpp 
		// to manage Book-type objects. 

		const std::string& getTitle() const { return m_title; };
		const unsigned getC() const { return m_numChapters; };
		const unsigned getP() const { return m_numPages; };
		
		// In completing Part 2, add here the missing 
		// member prototypes that would be necessary for 
		// OrderedCollection module code and tester module 
		// w3_p2.cpp to manage Book-type object. 
		//
		// Write the implementations of these functions 
		// in Book.cpp file

		std::ostream& print(std::ostream& os) const;
	};

	std::ostream& operator<<(std::ostream& os, const Book& bk);
}
#endif // !SDDS_BOOK_H