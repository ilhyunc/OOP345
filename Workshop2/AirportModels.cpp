#include "AirportModels.h"

#include<fstream>
#include<iomanip>
#include <string>

using namespace std;
namespace sdds {
    std::ostream& operator<<(std::ostream& os, const Airport& obj)
    {
        if (obj.m_code.empty())
        {
            os << "Empty Airport";
        }
        else
        {//setfill은 디폴트가 없음. 설정해주면 해제할때까지 출력댐. 
            os << setw(20) << right << setfill('.') << "Airport Code" << " : " << setw(30) << left << obj.m_code << endl;
            os << setw(20) << right << "Airport Name" << " : " << setw(30) << left << obj.m_name << endl;
            os << setw(20) << right << "City" << " : " << setw(30) << left << obj.m_city << endl;
            os << setw(20) << right << "State" << " : " << setw(30) << left << obj.m_state << endl;
            os << setw(20) << right << "Country" << " : " << setw(30) << left << obj.m_country << endl;
            os << setw(20) << right << "Latitude" << " : " << setw(30) << left << obj.m_latitude << endl;
            os << setw(20) << right << "Longitude" << " : " << setw(30) << left << obj.m_longtidue << endl;
        }
        //설정해제 
        os << setfill(' ');

        return os;
    }

   /* AirportLog::AirportLog() : m_airports{}, m_count(0)
    {
    }*/

    AirportLog::AirportLog(const char* filename) : m_airports{}, m_count(0) {
        ifstream is(filename);
        string temp;
        size_t numOfLines = 0;

        getline(is, temp);// scv파일 헤더 포함하지 않기 위해.
        while (getline(is, temp))
        {
            numOfLines++;
        }
        m_count = numOfLines;
        m_airports = new Airport[m_count];

        is.clear();//txt파일의 마지막 EOF를 읽고 -1, false가 되어있기때문에 초기화.
        is.seekg(0);//cusor를 처음으로 돌림(카운트 한다고 커서가 맨밑에 있는것을 처음으로 )

        getline(is, temp);

        for (size_t i = 0; i < m_count; i++)
        {
            getline(is, m_airports[i].m_code, ',');
            getline(is, m_airports[i].m_name, ',');
            getline(is, m_airports[i].m_city, ',');
            getline(is, m_airports[i].m_state, ',');
            getline(is, m_airports[i].m_country, ',');
            is >> m_airports[i].m_latitude;//double type
            is.ignore(); //파일 뒤에 ,가 있기 때문에.
            is >> m_airports[i].m_longtidue;//double type
            is.ignore(); //파일 뒤에 ,가 있기 때문에.
        }
    }

    void AirportLog::addAirport(const Airport& obj)
    {
        Airport* temp = m_airports;  //temp의 주소가 m_airports랑 같아짐.
        // m_airpots는 동적할당으로 temp보다 한자리 더 많게 사이즈를 늘려줌
        m_airports = new Airport[m_count + 1];
        for (size_t i = 0; i < m_count; i++)
        {//대입
            m_airports[i] = temp[i];
        }
        //한자리 더 늘려준 자리에 들어오는 obj를 넣어서 기존보다 데이터 +1
        m_airports[m_count] = obj;
        m_count++;
        delete[] temp;
    }

    //AirportLog& AirportLog::~~~, &사용시 rule of 3사용됨. 그리고 자료 복사를 '&'위해 안씀
    AirportLog AirportLog::findAirport(const char* m_state, const char* m_country) const {
        AirportLog found; //지역변수로 쓰기위해
        for (size_t i = 0; i < m_count; i++) 
        {
            if (m_airports[i].m_state == m_state && m_airports[i].m_country == m_country) 
            {
                found.addAirport(m_airports[i]);
            }
        }// &사용시 원본사용이기 때문에 found를 return 해도 원본은 변경 X 그래서 &이 사용.
        return found;
    }

    Airport& AirportLog::operator[](size_t index) const
    {//&사용은 원본사용한다는 뜻
        static Airport empty; // 원본사용하기때문에 static으로 선언
        return m_count > 0 ? m_airports[index % m_count] : empty;
    }

    //Airport AirportLog::operator[](size_t index) const
    //{// &사용안하면 사본 쓴다는 뜻
    //    Airport empty; // 사본사용하기 때문에 지역변수라 static 필요X
    //    return m_count > 0 ? m_airports[index % m_count] : empty;
    //}

    AirportLog::operator size_t() const
    {
        return m_count;
    }

    AirportLog::~AirportLog()
    {
        delete[] m_airports;
    }

    AirportLog::AirportLog(const AirportLog& I)
    {
        *this = I;
    }

    AirportLog& AirportLog::operator=(const AirportLog& other)
    {
        if (this != &other)
        {
            delete[] m_airports;
            m_count = other.m_count;
            m_airports = new Airport[m_count];
            
            for (size_t i = 0; i < m_count; i++)
            {
                m_airports[i] = other.m_airports[i];
            }
        }

        return *this;
    }

    AirportLog::AirportLog(AirportLog&& I) noexcept
    {   //std::move() =  l-value를 r-value처럼 쓰고 초기화 시키겠다는뜻.
        //std::move() 사용후 ()안의 value는 r-value처럼 소멸됨!
        *this = std::move(I);
    }

    AirportLog& AirportLog::operator=(AirportLog&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_airports;
            m_count = other.m_count;
            m_airports = other.m_airports;
            //초기화 해줌. 기존데이터는 필요없기때문에.
            other.m_airports = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

}