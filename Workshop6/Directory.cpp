#include "Directory.h"

namespace sdds {
    Directory::Directory(const std::string& name) {
        m_name = name;
        if (!name.empty() && name.back() != '/')
            m_name += '/';
    }

    void Directory::update_parent_path(const std::string& path) {
        m_parent_path = path;
        for (auto resource : m_contents) {
            resource->update_parent_path(path + m_name);
        }
    }

    NodeType Directory::type() const {
        return NodeType::DIR;
    }

    std::string Directory::path() const {
        if (m_parent_path.empty() || m_parent_path == "/") {
            return "/" + m_name;
        }
        return m_parent_path + m_name;
    }

    std::string Directory::name() const {
        return m_name;
    }

    int Directory::count() const {
        return static_cast<int>(m_contents.size());
    }

    size_t Directory::size() const {
        size_t totalSize = 0;
        for (auto resource : m_contents) {
            totalSize += resource->size();
        }
        return totalSize;
    }

    Directory& Directory::operator+=(Resource* resource) {
        for (auto existing : m_contents) {
            if (existing->name() == resource->name()) {
                throw std::runtime_error("Resource with the same name already exists");
            }
        }
        resource->update_parent_path(m_parent_path + m_name);
        m_contents.push_back(resource);
        return *this;
    }

    Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
        for (auto resource : m_contents) {
            if (resource->name() == name) {
                return resource;
            }
            if (resource->type() == NodeType::DIR && containsFlag(flags, OpFlags::RECURSIVE)) {
                Directory* dir = dynamic_cast<Directory*>(resource);
                if (dir) {
                    Resource* found = dir->find(name, flags);
                    if (found) {
                        return found;
                    }
                }
            }
        }
        return nullptr;
    }

    Directory::~Directory() {
        for (auto resource : m_contents) {
            delete resource;
        }
    }

    bool Directory::containsFlag(const std::vector<OpFlags>& flags, OpFlags flag) {
        return std::find(flags.begin(), flags.end(), flag) != flags.end();
    }
}
