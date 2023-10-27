#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <iomanip>

#include "RideRequest.h"

double g_taxrate{ 0 };
double g_discount{ 0 };

using namespace std;
namespace sdds {
	void RideRequest::setEmpty()
	{
		m_customerName[0] = '\0';
		delete[] m_rideDescription; // Deallocate memory!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		m_rideDescription = nullptr; // and set to nullptr!!!!!!!!!!!!!!!!!!!!!!!!!!!
		m_price = 0.0;
		m_discounted = false;
	}

	RideRequest::RideRequest() : m_customerName{}, m_rideDescription{}, m_price(0.0), m_discounted(false)
	{
	}

	RideRequest::RideRequest(const RideRequest& other) : m_customerName{}, m_rideDescription{}, m_price(0.0), m_discounted(false)
	{
		*this = other;
	}

	RideRequest& RideRequest::operator=(const RideRequest& other)
	{
		if (this != &other)
		{
			setEmpty();
			strcpy(m_customerName, other.m_customerName);
			if (other.m_rideDescription)
			{
				m_rideDescription = new char[strlen(other.m_rideDescription) + 1];
				strcpy(m_rideDescription, other.m_rideDescription);
			}

			m_price = other.m_price;
			m_discounted = other.m_discounted;
		}

		return *this;
	}

	RideRequest::~RideRequest()
	{
		delete[] m_rideDescription;
	}

	void RideRequest::read(std::istream& is)
	{
		is.getline(m_customerName, 10, ',');// ,까지 읽은후 ,를 버림

		char tempDesc[256];
		is.getline(tempDesc, 256, ','); // ,까지 읽은후 ,를 버림

		delete[] m_rideDescription;
		m_rideDescription = new char[strlen(tempDesc) + 1];
		strcpy(m_rideDescription, tempDesc); // 받아온 자료 대입!!!

		is >> m_price;
		is.ignore();

		char discountStatus;
		is >> discountStatus;

		// Set the discount flag based on the read status
		m_discounted = (discountStatus == 'Y');
		is.ignore();

		// Clear the istream error state if necessary
		if (!is.good()) 
		{
			is.clear();
			setEmpty(); // Set customer name to empty if read failed
		}
	}

	void RideRequest::display() const
	{
		static int counter = 0; // stactic variable(class variable): 메모리에 한번만 할당되어 모든 인스턴스 or 함수가 공유하는 변수.

		counter++;
		cout << left << setw(2) << counter << ". ";

		if (m_customerName[0] == '\0') 
		{
			cout << "No Ride Request" << endl;
		}
		else 
		{
			double taxedPrice = m_price * (1 + g_taxrate);
			double finalPrice = m_discounted ? (taxedPrice - g_discount) : taxedPrice;

			cout << setw(10) << m_customerName << "|" << setw(25) << m_rideDescription << "|" << fixed << setprecision(2) << setw(12) << taxedPrice << "|";

			if (m_discounted) 
			{
				cout << right << setw(13) << finalPrice;
			}

			cout << endl;
		}
	}
}



void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

int main(void) {//dereferencing
	int c = 3;
	int d = 10;
	swap(c, d);
	cout << "C: " << c << " D: " << d;
}