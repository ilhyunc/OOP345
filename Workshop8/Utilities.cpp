// Workshop 8 - Smart Pointers
// 2019/11 - Cornel

#include <memory>
#include <utility>
#include "DataBase.h"
#include "Profile.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	DataBase<Profile> excludeRaw(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles) {
		DataBase<Profile> result;
		// TODO: Add your code here to build a collection of Profiles.
		//         The result should contain only profiles from `allProfiles`
		//         which are not in `bannedProfiles` using Raw Pointers.
		
        for (size_t i = 0; i < allProfiles.size(); i++) 
        {
            const Profile& currentProfile = allProfiles[i];

            bool flag = false;
            for (size_t j = 0; j < bannedProfiles.size() && !flag; j++) 
            {
                if (currentProfile.m_age == bannedProfiles[j].m_age &&
                    currentProfile.m_name.first_name == bannedProfiles[j].m_name.first_name &&
                    currentProfile.m_name.last_name == bannedProfiles[j].m_name.last_name) 
                {
                    flag = true;
                }
            }

            if (!flag)
            {
                Profile* pptr = new Profile(currentProfile.m_name, currentProfile.m_address, currentProfile.m_age);
                try {
                    pptr->validateAddress();
                    result += pptr;
                }
                catch (...) {
                    delete pptr;
                    throw;
                }

                delete pptr;
            }
        }
		return result;
	}

    DataBase<Profile> excludeSmart(const DataBase<Profile>& allProfiles, const DataBase<Profile>& bannedProfiles)
    {
        DataBase<Profile> result;

        for (size_t i = 0; i < allProfiles.size(); i++)
        {
            const Profile& currentProfile = allProfiles[i];

            bool flag = false;
            for (size_t j = 0; j < bannedProfiles.size() && !flag; j++) 
            {
                if (currentProfile.m_age == bannedProfiles[j].m_age &&
                    currentProfile.m_name.first_name == bannedProfiles[j].m_name.first_name &&
                    currentProfile.m_name.last_name == bannedProfiles[j].m_name.last_name) 
                {
                    flag = true;
                }
            }

            if (!flag)
            {
                std::unique_ptr<Profile> smartPtr = std::make_unique<Profile>(currentProfile.m_name, currentProfile.m_address, currentProfile.m_age);
                    smartPtr->validateAddress();
                    result += std::move(smartPtr);
            }
        }

        return result;
    }
}
