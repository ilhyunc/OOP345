#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>

extern double g_taxrate; // extern은 전역변수에 declare만" 하는것.
extern double g_discount; // 여러군데 include가능하기때문에 extern 사용, 
// 그래서 cpp 파일에서 define 해줘야함.

namespace sdds {
	class RideRequest
	{
		char m_customerName[10]{};
		char* m_rideDescription{};
		double m_price;
		bool m_discounted;
		void setEmpty();
	public:
		RideRequest();
		RideRequest(const RideRequest& other);
		RideRequest& operator=(const RideRequest& other);
		~RideRequest();

		void read(std::istream& is);
		void display() const;

	};

}
#endif // !SDDS_RIDEREQUEST_H