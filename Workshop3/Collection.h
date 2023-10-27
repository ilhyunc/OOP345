#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H

#include <iostream>

#include "Book.h"

namespace sdds {
    template <typename T, size_t C>
    class Collection {
        T m_items[C]{};
        size_t m_size{};
        static T m_smallestItem;
        static T m_largestItem;
    protected: // public함수가 private 멤버에 접근하기 위해 getter사용하는 예시   
        void setSmallestItem(const T& item) { m_smallestItem = item; }
        void setLargestItem(const T& item){ m_largestItem = item; }
    public:
        T operator[](size_t index) const{
            if (index < m_size)
                return m_items[index % m_size];
            else
                return T{};
        }
        void incrSize() { m_size++;}

        Collection() {};

        T getSmallestItem() const { return m_smallestItem;}

        T getLargestItem() const { return m_largestItem;}

        size_t size() const { return m_size; }

        size_t capacity() const { return C;}

        virtual bool operator+=(const T& item) {
            bool result = false;
            if (m_size < C)
            {
                m_items[m_size++] = item;
                if (m_size == 1)
                {
                    m_smallestItem = item;
                    m_largestItem = item;
                }
                else
                {
                    if (item < m_smallestItem)
                    {
                        m_smallestItem = item;
                    }

                    if (item > m_largestItem)
                    {
                        m_largestItem = item;
                    }
                }

                result = true;
            }
            return result;
        }

        std::ostream& print(std::ostream& os) const
        {
            os << "[";
            for (size_t i = 0; i < m_size; ++i)
            {
                os << m_items[i];
                if (i + 1 != m_size)
                {
                    os << ",";
                }
            }
            os << "]" << std::endl;

            return os;

        }

        T* getter() { return m_items; } //reference 사용시 한번 초기화되면 다른객체를 참조 할수 없지만 포인터는 nullptr을 사용,
        //함수가 배열의 일부 요소를 반환하려는 것이라면, 일반적으로 포인터를 반환하는 것이 적합합니다.
        // T m_items[C] 가 array이기 때문에 포인터가 더 적절.
        // 만약 T m_items; 였다면 &가 더적절함.
    };


    //class에서 static 변수는 무조건 따로 초기화!
    template <typename T, size_t C> //위와동일함!
    T Collection<T, C>::m_smallestItem = T{};

    template<> //specialization 특정한경우에만!
    int Collection<int, 10>::m_largestItem{};
    template<>
    double Collection<double, 10>::m_largestItem{};
    template <>                     //Book class의 private변수 갯수랑 같음
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);
    template <>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);
    template<>
    std::ostream& Collection<Book, 10>::print(std::ostream& os) const {
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        for (size_t i = 0; i < this->size(); ++i)
        {
            os << "| ";
            m_items[i].print(os);
            os << " |" << std::endl;
        }
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        return os;
    }


    template<>
    int Collection<int, 72>::m_largestItem{};
    template<>
    double Collection<double, 72>::m_largestItem{};
    template <>
    Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);
    template <>
    Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);
    template<>
    std::ostream& Collection<Book, 72>::print(std::ostream& os) const {
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        for (size_t i = 0; i < this->size(); ++i)
        {
            os << "| ";
            m_items[i].print(os);
            os << " |" << std::endl;
        }
        os << "| ---------------------------------------------------------------------------|" << std::endl;
        return os;
    }

}
#endif // SDDS_COLLECTION_H