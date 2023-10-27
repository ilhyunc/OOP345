#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>

namespace sdds {
	struct Airport { // struct������ default�� public
		std::string m_code{}; // = {""}(default)
		std::string m_name{};
		std::string m_city{};
		std::string m_state{};
		std::string m_country{};
		double m_latitude{};
		double m_longtidue{};
	};
	std::ostream& operator<<(std::ostream& os, const Airport& obj); //getter ������ �������� �������� ��� ������ public�̿�����. 
	//struct������ default�� public

	class AirportLog
	{ // struct������ default�� private
		Airport* m_airports{};//dinamic array
		size_t m_count{}; // size_t �� �������� ���
	public:
		AirportLog() {};
		AirportLog(const char* filename); 
		
		void addAirport(const Airport& obj);
		AirportLog findAirport(const char* m_state, const char* m_country) const;

		Airport& operator[](size_t index) const;
		operator size_t() const;

		//Rule of 5!
		~AirportLog();
		AirportLog(const AirportLog& I);
		AirportLog& operator=(const AirportLog& other);
		AirportLog(AirportLog&& I) noexcept; // move constructor , "noexcept"�� �߰��� ����°� ��� X��
		AirportLog& operator=(AirportLog&& other) noexcept; // move assignment function
	};

}
#endif // !SDDS_AIRPORTMODELS_H