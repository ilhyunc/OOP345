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
        {//setfill�� ����Ʈ�� ����. �������ָ� �����Ҷ����� ��´�. 
            os << setw(20) << right << setfill('.') << "Airport Code" << " : " << setw(30) << left << obj.m_code << endl;
            os << setw(20) << right << "Airport Name" << " : " << setw(30) << left << obj.m_name << endl;
            os << setw(20) << right << "City" << " : " << setw(30) << left << obj.m_city << endl;
            os << setw(20) << right << "State" << " : " << setw(30) << left << obj.m_state << endl;
            os << setw(20) << right << "Country" << " : " << setw(30) << left << obj.m_country << endl;
            os << setw(20) << right << "Latitude" << " : " << setw(30) << left << obj.m_latitude << endl;
            os << setw(20) << right << "Longitude" << " : " << setw(30) << left << obj.m_longtidue << endl;
        }
        //�������� 
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

        getline(is, temp);// scv���� ��� �������� �ʱ� ����.
        while (getline(is, temp))
        {
            numOfLines++;
        }
        m_count = numOfLines;
        m_airports = new Airport[m_count];

        is.clear();//txt������ ������ EOF�� �а� -1, false�� �Ǿ��ֱ⶧���� �ʱ�ȭ.
        is.seekg(0);//cusor�� ó������ ����(ī��Ʈ �Ѵٰ� Ŀ���� �ǹؿ� �ִ°��� ó������ )

        getline(is, temp);

        for (size_t i = 0; i < m_count; i++)
        {
            getline(is, m_airports[i].m_code, ',');
            getline(is, m_airports[i].m_name, ',');
            getline(is, m_airports[i].m_city, ',');
            getline(is, m_airports[i].m_state, ',');
            getline(is, m_airports[i].m_country, ',');
            is >> m_airports[i].m_latitude;//double type
            is.ignore(); //���� �ڿ� ,�� �ֱ� ������.
            is >> m_airports[i].m_longtidue;//double type
            is.ignore(); //���� �ڿ� ,�� �ֱ� ������.
        }
    }

    void AirportLog::addAirport(const Airport& obj)
    {
        Airport* temp = m_airports;  //temp�� �ּҰ� m_airports�� ������.
        // m_airpots�� �����Ҵ����� temp���� ���ڸ� �� ���� ����� �÷���
        m_airports = new Airport[m_count + 1];
        for (size_t i = 0; i < m_count; i++)
        {//����
            m_airports[i] = temp[i];
        }
        //���ڸ� �� �÷��� �ڸ��� ������ obj�� �־ �������� ������ +1
        m_airports[m_count] = obj;
        m_count++;
        delete[] temp;
    }

    //AirportLog& AirportLog::~~~, &���� rule of 3����. �׸��� �ڷ� ���縦 '&'���� �Ⱦ�
    AirportLog AirportLog::findAirport(const char* m_state, const char* m_country) const {
        AirportLog found; //���������� ��������
        for (size_t i = 0; i < m_count; i++) 
        {
            if (m_airports[i].m_state == m_state && m_airports[i].m_country == m_country) 
            {
                found.addAirport(m_airports[i]);
            }
        }// &���� ��������̱� ������ found�� return �ص� ������ ���� X �׷��� &�� ���.
        return found;
    }

    Airport& AirportLog::operator[](size_t index) const
    {//&����� ��������Ѵٴ� ��
        static Airport empty; // ��������ϱ⶧���� static���� ����
        return m_count > 0 ? m_airports[index % m_count] : empty;
    }

    //Airport AirportLog::operator[](size_t index) const
    //{// &�����ϸ� �纻 ���ٴ� ��
    //    Airport empty; // �纻����ϱ� ������ ���������� static �ʿ�X
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
    {   //std::move() =  l-value�� r-valueó�� ���� �ʱ�ȭ ��Ű�ڴٴ¶�.
        //std::move() ����� ()���� value�� r-valueó�� �Ҹ��!
        *this = std::move(I);
    }

    AirportLog& AirportLog::operator=(AirportLog&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_airports;
            m_count = other.m_count;
            m_airports = other.m_airports;
            //�ʱ�ȭ ����. ���������ʹ� �ʿ���⶧����.
            other.m_airports = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

}