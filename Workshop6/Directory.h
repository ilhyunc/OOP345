#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Resource.h"
#include "Flags.h"
#include <vector>

namespace sdds {
    class Directory : public Resource {
    private:
        std::vector<Resource*> m_contents{};

    public:
        Directory(const std::string& name);

        void update_parent_path(const std::string& path);
        NodeType type() const;
        std::string path() const;
        std::string name() const;
        int count() const;
        size_t size() const;

        Directory& operator+=(Resource* resource);
        Resource* find(const std::string& name, const std::vector<OpFlags>& flags = {});
        ~Directory();

        bool containsFlag(const std::vector<OpFlags>& flags, OpFlags flag);
        Directory(const Directory& other) = delete;
        Directory& operator=(const Directory& other) = delete;
        Directory(Directory&& other) = delete;
        Directory& operator=(Directory&& other) = delete;
    };
}

#endif
