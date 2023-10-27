#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H

#include "Cheese.h"

namespace sdds {
    class CheeseParty {
        const Cheese** m_cheeses{};
        size_t m_size{};
    public:
        CheeseParty() {}

        CheeseParty(const CheeseParty& I);
        CheeseParty(CheeseParty&& I) noexcept;
        CheeseParty& operator=(const CheeseParty& other);
        CheeseParty& operator=(CheeseParty&& other) noexcept;
        ~CheeseParty();

        CheeseParty& addCheese(const Cheese& cheese);
        CheeseParty& removeCheese();

        friend std::ostream& operator<<(std::ostream& os, const CheeseParty& party);
    };
}

#endif

