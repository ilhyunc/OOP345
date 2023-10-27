#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>

namespace sdds {
	struct Airport { // struct에서는 default가 public
		std::string m_code{}; // = {""}(default)
		std::string m_name{};
		std::string m_city{};
		std::string m_state{};
		std::string m_country{};
		double m_latitude{};
		double m_longtidue{};
	};
	std::ostream& operator<<(std::ostream& os, const Airport& obj); //getter 사용없이 가져오고 있음으로 멤버 변수가 public이여야함. 
	//struct에서는 default가 public

	class AirportLog
	{ // struct에서는 default가 private
		Airport* m_airports{};//dinamic array
		size_t m_count{}; // size_t 는 정수에만 사용
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
		AirportLog(AirportLog&& I) noexcept; // move constructor , "noexcept"는 중간에 끊기는거 허용 X뜻
		AirportLog& operator=(AirportLog&& other) noexcept; // move assignment function
	};

}
#endif // !SDDS_AIRPORTMODELS_H