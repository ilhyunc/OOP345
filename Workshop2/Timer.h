#ifndef SDDS_TIMER_H
#define SDDS_TIMER_H
#include <chrono>
#include <string>

namespace sdds {
	class Timer {
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_endTime;
	public:
		void start();
		long long stop();
	};
}

#endif