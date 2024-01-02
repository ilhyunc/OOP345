#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "CovidCollection.h"

using namespace std;
namespace sdds {
	void trim(string& src)
	{
		if (src.length() > 0)
		{
			int begin = src.find_first_not_of(' ');
			int end = src.find_last_not_of(' ');
			if (begin == -1)
			{
				src = "";
			}
			else
			{
				src = src.substr(begin, end - begin + 1);
			}
		}
	}

	CovidCollection::CovidCollection(string filename)
	{
		ifstream file(filename);
		if (!file)
		{
			throw "ERROR: filename is incorrect";
		}

		Covid tempCovid;
		string temp;
		do {
			getline(file, temp);
			if (file) {
				tempCovid.m_country = temp.substr(0, 25);
				trim(tempCovid.m_country);

				tempCovid.m_city = temp.substr(25, 25);
				trim(tempCovid.m_city);

				tempCovid.m_variant = temp.substr(50, 25);
				trim(tempCovid.m_variant);

				tempCovid.m_year = stoi(temp.substr(75, 5));
				tempCovid.m_cases = stoi(temp.substr(80, 5));
				tempCovid.m_deaths = stoi(temp.substr(85, 5));

				m_covidCollection.push_back(tempCovid);//
			}
		} while (file);
		//필요없음
		//file.close();
	} // 여기서 자동으로 파일 닫힘.

	void CovidCollection::display(std::ostream& out, const std::string& country) const
	{
		size_t totalCases = 0;
		size_t totalDeaths = 0;

		auto printCovid = [&](Covid theCovid) {
			out << theCovid << endl;
			};

		if (country == "ALL")
		{
			std::for_each(m_covidCollection.begin(), m_covidCollection.end(), [&](const auto& covid) {
				printCovid(covid);
				totalCases += covid.m_cases;
				totalDeaths += covid.m_deaths;
			});
			out << "| " << std::right << std::setw(79) << "Total cases around the world: " << totalCases << " |" << endl;
			out << "| " << std::setw(79) << "Total deaths around the world: " << totalDeaths << " |" << endl;
		}
		else
		{
			size_t countryCases = 0;
			size_t countryDeaths = 0;

			out << "Displaying information of country = " << country << endl;

			std::for_each(m_covidCollection.begin(), m_covidCollection.end(), [&](const auto& covid) {
				if (covid.m_country == country)
				{
					printCovid(covid);
					countryCases += covid.m_cases;
					countryDeaths += covid.m_deaths;
				}
				totalCases += covid.m_cases;
				totalDeaths += covid.m_deaths;
				});

			double casesPercentage = ((double)countryCases / totalCases) * 100;
			double deathsPercentage = ((double)countryDeaths / totalDeaths) * 100;

			out << "----------------------------------------------------------------------------------------" << endl;
			out << "| " << setw(78) << "Total cases in " + country << ": " << countryCases << " |" << endl;
			out << "| " << setw(78) << "Total deaths in " + country << ": " << countryDeaths << " |" << endl;

			if (casesPercentage > 10.0 && deathsPercentage > 10.0)
			{
				out << "| " << setw(26);
			}
			else if (casesPercentage > 10.0 || deathsPercentage > 10.0)
			{
				out << "| " << setw(27);
			}
			else
			{
				out << "| " << setw(28);
			}
			out << country + " has " << fixed << setprecision(6)
				<< casesPercentage << "% of global cases and " << deathsPercentage << "% of global deaths |" << std::endl;
		}
	}


	void CovidCollection::sort(const std::string& field) 
	{
		auto comparator = [field](const Covid& a, const Covid& b) {
			if (field == "variant")
			{
				if (a.m_variant == b.m_variant)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_variant < b.m_variant;
			}
			else if (field == "year")
			{
				if (a.m_year == b.m_year)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_year < b.m_year;
			}
			else
			{
				if (a.m_country == b.m_country)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_country < b.m_country;
			}
			};

		std::sort(m_covidCollection.begin(), m_covidCollection.end(), comparator);
	}

	bool CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const 
	{
		return std::any_of(m_covidCollection.begin(), m_covidCollection.end(), [&](Covid covid) { return covid.m_country == country && covid.m_variant == variant && covid.m_deaths > deaths; });
	}

	std::list<Covid> CovidCollection::getListForDeaths(unsigned int deaths) const
	{
		list<Covid> result;
		std::copy_if(m_covidCollection.begin(), m_covidCollection.end(), back_inserter(result), [&](Covid covid) { return covid.m_deaths >= deaths; });

		return result;
	}

	void CovidCollection::updateStatus() 
	{
		std::for_each(m_covidCollection.begin(), m_covidCollection.end(), [](Covid& covid) {
			if (covid.m_deaths > 300) 
			{
				covid.m_status = "EPIDEMIC";
			}
			else if (covid.m_deaths < 50) 
			{
				covid.m_status = "EARLY";
			}
			else 
			{
				covid.m_status = "MILD";
			}
			});
	}

	std::ostream& operator<<(std::ostream& out, const Covid& theCovid)
	{
		out << "| " << setw(21) << left << theCovid.m_country << " | "
			<< setw(15) << left << theCovid.m_city << " | "
			<< setw(20) << left << theCovid.m_variant << " | "
			<< setw(6) << right;

		if (theCovid.m_year < 0)// m_year을 size_t로 쓰면 임의의 숫자로 0보다 크게 나옴.int로 사용해야 -그대로 인지
		{
			out << ' ';
		}
		else
		{
			out << theCovid.m_year;
		}

		out << " | "
			<< setw(4) << theCovid.m_cases << " | "
			<< setw(3) << theCovid.m_deaths << " |"
			<< " | " << right << setw(8) << theCovid.m_status << " |";

		return out;
	}

}