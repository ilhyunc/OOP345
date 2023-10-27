#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H

#include <iostream>

namespace sdds {
    class Cheese {
        std::string m_name;
        size_t m_weight{};
        double m_price{};
        std::string m_features1{};
        std::string m_features2{};
        std::string m_features3{};

    public:
        Cheese() :m_name("NaC") {}
        Cheese(const std::string& str);
        Cheese slice(size_t weight);

        size_t getWeight() const;

        friend std::ostream& operator<<(std::ostream& os, const Cheese& cheese);
    };
}

#endif



