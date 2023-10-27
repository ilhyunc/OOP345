#ifndef SDDS_ORDEREDCOLLECTION_H
#define SDDS_ORDEREDCOLLECTION_H
#include "Collection.h"
namespace sdds {
    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:
        bool operator+=(const T& item) {
            if (this->size() >= this->capacity())
            { return false; }

            size_t newIndex = 0;
            while (newIndex < this->size() && item > this->getter()[newIndex])
            { newIndex++; }

            for (size_t i = this->size(); i > newIndex; --i)
            { this->getter()[i] = this->getter()[i - 1]; }

            this->getter()[newIndex] = item;
            this->incrSize();

            if (this->size() == 1) {
                this->setSmallestItem(item);
                this->setLargestItem(item);
            }
            else {
                if (item < this->getSmallestItem()) 
                {this->setSmallestItem(item);}
                if (item > this->getLargestItem()) 
                { this->setLargestItem(item); }
            }

            return true;
        }

    };
}

#endif // SDDS_ORDEREDCOLLECTION_H
