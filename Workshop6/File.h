#ifndef FILE_H
#define FILE_H

#include "Resource.h"

namespace sdds {
    class File : public Resource {
        std::string m_contents{};
    public:
        File(const std::string& name, const std::string& contents);

        void update_parent_path(const std::string& path);
        NodeType type() const;
        std::string path() const;
        std::string name() const;
        int count() const;
        size_t size() const;
    };
}

#endif
