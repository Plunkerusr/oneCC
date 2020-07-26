#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>

namespace oneCC::CodeGenerator::Aarch32 {

class VarManager {
public:
    VarManager() = default;

    int addStackVarible(std::string alias, int offset)
    {
        m_storage[std::make_pair(alias, m_level)] = offset;
        return 0;
    }

    // Will return 0, if no such value
    int getStackVarible(std::string alias)
    {
        return m_storage[std::make_pair(alias, m_level)];
    }

    void enterScope() { m_level++; }

    void leaveScope()
    {
        auto it = m_storage.begin();
        while (m_storage.end() != (it = std::find_if(m_storage.begin(), m_storage.end(), [this](auto p) { return p.first.second == m_level; }))) {
            m_storage.erase(it);
        }
        m_level--;
    }

    void dump()
    {
        std::cout << "--- VarManager Storage Dump ---\n";
        for (auto entry : m_storage) {
            std::cout << entry.first.first << " " << entry.first.second << " = " << entry.second << "\n";
        }
        std::cout << "--- VarManager Storage End ----\n";
    }

private:
    int m_level { 0 };
    std::map<std::pair<std::string, int>, int> m_storage;
};

}