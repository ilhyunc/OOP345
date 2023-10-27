#include "Cheese.h"
#include <sstream>
#include <iomanip>

using namespace std;
namespace sdds {
    string trim(string& str) //&�� ����ϴ� ������ ������ �����ϴ°Ŷ�.
    {
        size_t start = str.find_first_not_of(' '); //������ �ƴ� ù ���ڿ��� ���۵Ǵ� index
        if (start == string::npos)
        {
            return "";
        }
        size_t end = str.find_last_not_of(' '); //������ �ƴ� ������ ���ڿ��� ������ index
        return str = str.substr(start, end - start + 1);//so,  +1������ ������ �ڸ� ���� ��¾ȵ�.
    }

    Cheese::Cheese(const string& str)
    {
        string temp = str;
        //Ŀ�������� 0��° index���� ','�������� ã�ƶ�.
        string name = temp.substr(0, temp.find(','));
        m_name = trim(name);
        temp.erase(0, temp.find(',') + 1); //','���� ã�ұ⶧����, ó������ ','���� ����

        m_weight = stoi(temp); //int type�� �б⶧���� ������ ���� �ʾƼ� trim�ʿ� XX
        temp.erase(0, temp.find(',') + 1);

        m_price = stod(temp);  //double type�� �б⶧���� ������ ���� �ʾƼ� trim�ʿ� XX
        temp.erase(0, temp.find(',') + 1);

        string features1 = temp.substr(0, temp.find(','));
        m_features1 = trim(features1);
        temp.erase(0, temp.find(',') + 1);

        string features2 = temp.substr(0, temp.find(','));
        m_features2 = trim(features2);
        temp.erase(0, temp.find(',') + 1);

        string features3 = temp.substr(0, temp.find(','));
        m_features3 = trim(features3);
    }

    Cheese Cheese::slice(size_t sliceWeight)
    {
        if (sliceWeight <= m_weight)
        {
            Cheese slicedCheese;
            slicedCheese.m_name = m_name;
            slicedCheese.m_weight = sliceWeight;
            slicedCheese.m_price = m_price;
            slicedCheese.m_features1 = m_features1;
            slicedCheese.m_features2 = m_features2;
            slicedCheese.m_features3 = m_features3;
            m_weight -= sliceWeight;
            return slicedCheese;
        }
        else 
        {
            return Cheese();
        }
    }

    size_t Cheese::getWeight() const
    {
        return m_weight;
    }

    ostream& operator<<(ostream& os, const Cheese& cheese) 
    {        
        os << "|" << left << setw(21) << cheese.m_name << "|" << setw(5) << cheese.m_weight << "|" << fixed << setw(5) << setprecision(2) << cheese.m_price << "|";
        if (cheese.m_features2 == cheese.m_features3)
        {
            os << setw(33) << right << cheese.m_features1 + " " + cheese.m_features2 << " |" << endl;
        }
        else 
        {
            os << setw(33) << right << cheese.m_features1 + " " + cheese.m_features2 + " " + cheese.m_features3 << " |" << endl;
        }
        return os;
    }
}