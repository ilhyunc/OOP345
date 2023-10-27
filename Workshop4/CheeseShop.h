#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H

#include "Cheese.h"

namespace sdds { //"Cheese.h"
    class CheeseShop {
        std::string m_shopName{};
        Cheese** m_cheeses{};
        size_t m_size{};
    public:
        CheeseShop() {}

        CheeseShop(std::string shopName) : m_shopName(shopName) {}
        CheeseShop(const CheeseShop& I);
        CheeseShop(CheeseShop&& I) noexcept;
        CheeseShop& operator=(const CheeseShop& other);
        CheeseShop& operator=(CheeseShop&& other) noexcept;
        ~CheeseShop();

        CheeseShop& addCheese(const Cheese& cheese);

        friend std::ostream& operator<<(std::ostream& os, const CheeseShop& shop);
    };
}

#endif
