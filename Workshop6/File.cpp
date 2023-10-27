#include "File.h"

using namespace std;

namespace sdds {
    File::File(const std::string& name, const std::string& contents) : m_contents(contents) 
    {//m_name = Resource.hø° ¿÷¿Ω
        m_name = name;
    }

    void File::update_parent_path(const std::string& path) 
    {
        m_parent_path = path;
    }

    NodeType File::type() const 
    {
        return NodeType::FILE;
    }

    std::string File::path() const 
    {
        string temp;
        if (m_parent_path.empty() || m_parent_path == "/")
        {
            temp = "/" + m_name;
        }
        else
        {
            temp = m_parent_path + m_name;
        }

        return temp;
    }

    std::string File::name() const 
    {
        return m_name;
    }

    int File::count() const
    {
        return -1;
    }

    size_t File::size() const 
    {
        return m_contents.size();
    }
}
