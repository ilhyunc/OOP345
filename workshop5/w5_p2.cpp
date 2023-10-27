// Workshop 5 - Functions and Error Handling
// 2021/01/19 - Chris
// 2021/02/12 - Cornel
// 2023/10/05 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"     // intentional
#include "SpellChecker.h"
#include "SpellChecker.h"   // intentional
#include "Book.h"
#include "Book.h"           // intentional
#include "Movie.h"
#include "Movie.h"          // intentional

using namespace sdds;

// 2020/02 - Cornel
// Cheching if header guards exist and follow convention.
#ifndef SDDS_BOOK_H
#error "The header guard for 'Book.h' doesn't follow the convention!"
#endif
#ifndef SDDS_MOVIE_H
#error "The header guard for 'Movie.h' doesn't follow the convention!"
#endif
#ifndef SDDS_SPELLCHECKER_H
#error "The header guard for 'SpellChecker.h' doesn't follow the convention!"
#endif
#ifndef SDDS_COLLECTION_H
#error "The header guard for 'Collection.h' doesn't follow the convention!"
#endif

int cout = 0; // won't compile if headers don't follow convention regarding namespaces

enum AppErrors
{ //output 화면에서 오류 넘버를 출력해서 어떤 오류인지 확인할수 있음
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const sdds::Collection<sdds::Book>& theCollection,
	const sdds::Book& theBook)
{
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const sdds::Collection<sdds::Movie>& theCollection,
	const sdds::Movie& theMovie)
{
	std::cout << "Movie \"" << theMovie.title()
		<< "\" added to collection \"" << theCollection.name()
		<< "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the books
	sdds::Collection<sdds::Book> library("Bestsellers");
	if (argc == 5) {
		// TODO: load the first 4 books from the file "argv[1]".
		//       - read one line at a time, and pass it to the Book constructor
		//       - store each book read into the collection "library" (use the += operator)
		//       - lines that start with "#" are considered comments and should be ignored
		//       - if the file cannot be open, print a message to standard error console and
		//                exit from application with error code "AppErrors::CannotOpenFile"
		std::ifstream file(argv[1]);
		std::string tempBook;

		if (file)
		{
			int index = 0;
			do
			{
				std::getline(file, tempBook);
				if (tempBook[0] != '#')
				{
					library += Book(tempBook);
					index++;
				}
			} while (index < 4);
		}
		else
		{
			std::cerr << "ERROR: Cannot open file named" << argv[1] << std::endl;
			exit(AppErrors::CannotOpenFile);
		}



		/*
		 ♪ Hey, I just met you,      ♪
		 ♪ And this is crazy,        ♪
		 ♪ But here's my number.     ♪    (register the observer)
		 ♪ So, if something happens, ♪    (event)
		 ♪ Call me, maybe?           ♪    (callback)
		 */
		library.setObserver(bookAddedObserver); //bookAddedObserver를 가르키는 주소를 인자로 전달한다. 함수포인터 setObserver의 사용법.

		// TODO: add the rest of the books from the file.
		do
		{
			std::getline(file, tempBook);
			if (file)
			{
				if (tempBook[0] != '#')
				{
					library += Book(tempBook);
				}
			}
		} while (file);

		file.close();
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}


	// TODO: (from part #1) create a lambda expression that fixes the price of a book accoding to the rules
	//       - the expression should receive a single parameter of type "Book&"
	//       - if the book was published in US, multiply the price with "usdToCadRate"
	//            and save the new price in the book object
	//       - if the book was published in UK between 1990 and 1999 (inclussive),
	//            multiply the price with "gbpToCadRate" and save the new price in the book object

	//함수 안의 함수 w5_p2.cpp라는 메인 함수안에서 
	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	/*람다 표현식 : 함수, 즉석에서 만든다
	[] : 캡쳐, 외부의 함수에 있는 변수들을 끌어와서 쓰겟다.여러개도 가능. '&' = call by address, '=' - call by value
	'&'만 사용시 외부의 모든 변수들을 허용하겠다는 뜻.
	() : 파라미터 - (Book& book) 원본을 사용(변경)하겠다.
	{} : 바디*/
	//변수가 함수처럼 역할을함.
	auto fixPrice = [usdToCadRate, gbpToCadRate](Book& book) {
		if (book.country() == "US") { book.price() = book.price() * usdToCadRate; }
			else if (book.country() == "UK" && book.year() >= 1990 && book.year() <= 1999)
			{ book.price() = book.price() * gbpToCadRate; }
	};

	
	//void(*fptr)(Book&) = setPrice; //sePrice = global 변수


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	// TODO (from part #1): iterate over the library and update the price of each book
	//         using the lambda defined above.
	for (size_t i = 0; i < library.size(); i++)
	{
		fixPrice(library[i]); //람다 표현식을 통해 가능해짐.
	}


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	Collection<Movie> theCollection("Action Movies");

	// Process the file
	Movie movies[5];
	if (argc > 2) {
		// TODO: load 5 movies from the file "argv[2]".
		//       - read one line at a time, and pass it to the Movie constructor
		//       - store each movie read into the array "movies"
		//       - lines that start with "#" are considered comments and should be ignored
		std::ifstream file(argv[2]);

		std::string tempMovie;

		if (file)
		{
			int index = 0;
			do
			{
				std::getline(file, tempMovie);
				if (tempMovie[0] != '#')
				{
					movies[index++] = Movie(tempMovie);
				}
			} while (index < 5);
		}
		else
		{
			std::cerr << "ERROR: Cannot open file named" << argv[1] << std::endl;
			exit(AppErrors::CannotOpenFile);
		}
	}


	std::cout << "-----------------------------------------\n";
	std::cout << "Testing addition and callback function\n";
	std::cout << "-----------------------------------------\n";
	if (argc > 2) {
		// Add a few movies to collection; no observer is set
		((theCollection += movies[0]) += movies[1]) += movies[2];
		theCollection += movies[1];
		// add more movies; now we get a callback from the collection
		theCollection.setObserver(movieAddedObserver);
		theCollection += movies[3];
		theCollection += movies[3];
		theCollection += movies[4];
	}
	else {
		std::cout << "** No movies in the Collection\n";
	}
	std::cout << "-----------------------------------------\n\n";

	std::cout << "-----------------------------------------\n";
	std::cout << "Testing exceptions and operator[]\n";
	std::cout << "-----------------------------------------\n";


	// TODO: The following loop can generate generate an exception
	//         write code to handle the exception
	//       If an exception occurs print a message in the following format
	//** EXCEPTION: ERROR_MESSAGE<endl>
	//         where ERROR_MESSAGE is extracted from the exception object.
	
	try 
	{
		for (auto i = 0u; i < 10; ++i)
			std::cout << theCollection[i];
	}
	catch(std::out_of_range& oor)
	{
		std::cout << "** EXCEPTION: " << oor.what() << std::endl; //.what()은 out_of_range exception일때 호출될 string
	}

	std::cout << "-----------------------------------------\n\n";


	std::cout << "-----------------------------------------\n";
	std::cout << "Testing the functor\n";
	std::cout << "-----------------------------------------\n";
	for (auto i = 3; i < argc; ++i)
	{
		// TODO: The following statement can generate generate an exception
		//         write code to handle the exception
		//       If an exception occurs print a message in the following format
		//** EXCEPTION: ERROR_MESSAGE<endl>
		//         where ERROR_MESSAGE is extracted from the exception object.
		try	{
			sdds::SpellChecker sp(argv[i]);
			for (auto j = 0u; j < library.size(); ++j)
				library[j].fixSpelling(sp);
			sp.showStatistics(std::cout);

			for (auto j = 0u; j < theCollection.size(); ++j)
				theCollection[j].fixSpelling(sp);
			sp.showStatistics(std::cout);
		}
		//데이터 타입마다 설정가능.
		catch (int a) { std::cout << a << std::endl; }
		catch (double b) { std::cout << b << std::endl; }
		catch (const char* msg) { std::cout << "** EXCEPTION: " << msg << std::endl; }
		catch (...)//throw하는 데이터 타입이랑 같아야함. 모를땐...사용(에러종류 확인 힘듦)
		{ std::cout << "Exeption Throw" << std::endl; } //...은 마지막으로
	}
	if (argc < 3) {
		std::cout << "** Spellchecker is empty\n";
		std::cout << "-----------------------------------------\n";
	}
	std::cout << "\n";

	std::cout << "=========================================\n";
	std::cout << "Wrapping up this workshop\n";
	std::cout << "--------------- Movies ------------------\n";
	std::cout << theCollection;
	std::cout << "--------------- Books -------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing operator[] (the other overload)\n";
	std::cout << "-----------------------------------------\n";
	const sdds::Movie* aMovie = theCollection["Terminator 2"];
	if (aMovie == nullptr)
		std::cout << "** Movie Terminator 2 not in collection.\n";
	aMovie = theCollection["Dark Phoenix"];
	if (aMovie != nullptr)
		std::cout << "In this collection:\n" << *aMovie;
	std::cout << "-----------------------------------------\n";

	return cout;
}