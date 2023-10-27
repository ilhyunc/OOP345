#ifndef SDDS_RIDEREQUEST_H
#define SDDS_RIDEREQUEST_H

#include <iostream>

extern double g_taxrate; // extern�� ���������� declare��" �ϴ°�.
extern double g_discount; // �������� include�����ϱ⶧���� extern ���, 
// �׷��� cpp ���Ͽ��� define �������.

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