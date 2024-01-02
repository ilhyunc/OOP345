#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H

#include <string>
#include <vector>
#include <list>

namespace sdds{
    struct Covid {
        std::string m_country{};
        std::string m_city{};
        std::string m_variant{};
        int m_year{};
        size_t m_cases{};
        size_t m_deaths{};

        std::string m_status{ "General" };
    };

    std::ostream& operator<<(std::ostream& out, const Covid& theCovid);

    class CovidCollection {
        std::vector<Covid> m_covidCollection;

    public:
        CovidCollection(std::string filename);
        void display(std::ostream& out, const std::string& country = "ALL") const;
        void sort(const std::string& field = "country");
        bool inCollection(const std::string& status, const std::string& country, unsigned int deaths) const;
        std::list<Covid> getListForDeaths(unsigned int deaths) const;
        void updateStatus();
    };
}

#endif
