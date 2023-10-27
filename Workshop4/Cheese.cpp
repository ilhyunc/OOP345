#include "Cheese.h"
#include <sstream>
#include <iomanip>

using namespace std;
namespace sdds {
    string trim(string& str) //&을 사용하는 이유는 원본을 수정하는거라서.
    {
        size_t start = str.find_first_not_of(' '); //여백이 아닌 첫 문자열이 시작되는 index
        if (start == string::npos)
        {
            return "";
        }
        size_t end = str.find_last_not_of(' '); //여백이 아닌 마지막 문자열이 끝나는 index
        return str = str.substr(start, end - start + 1);//so,  +1없으면 마지막 자리 문자 출력안됨.
    }

    Cheese::Cheese(const string& str)
    {
        string temp = str;
        //커서시작인 0번째 index부터 ','이전까지 찾아라.
        string name = temp.substr(0, temp.find(','));
        m_name = trim(name);
        temp.erase(0, temp.find(',') + 1); //','까지 찾았기때문에, 처음부터 ','까지 삭제

        m_weight = stoi(temp); //int type만 읽기때문에 여백은 읽지 않아서 trim필요 XX
        temp.erase(0, temp.find(',') + 1);

        m_price = stod(temp);  //double type만 읽기때문에 여백은 읽지 않아서 trim필요 XX
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