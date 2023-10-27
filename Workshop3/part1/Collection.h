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

    protected:
        void setSmallestItem(const T& item) 
        {
            if (item < m_smallestItem)
                m_smallestItem = item;
        }

        void setLargestItem(const T& item)
        {
            if (item > m_largestItem)
                m_largestItem = item;
        }

    public:
        Collection() {};

        T getSmallestItem() const 
        {
            return m_smallestItem;
        }

        T getLargestItem() const 
        {
            return m_largestItem;
        }

        size_t size() const
        {
            return m_size;
        }

        size_t capacity() const
        {
            return C;
        }

        bool operator+=(const T& item) 
        {
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
                    else if(item > m_largestItem)
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
    };

    template <typename T, size_t C>
    T Collection<T, C>::m_smallestItem = T();

    template <>
    Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

    template <>
    Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

    template<>
    int Collection<int, 10u>::m_largestItem = 0;

    template<>
    double Collection<double, 10u>::m_largestItem = 0.0;

}
#endif // SDDS_COLLECTION_H