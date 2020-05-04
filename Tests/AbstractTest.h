#pragma once
#include <string>
#include <vector>

#include "../Utils/Utils.h"

namespace oneCC::Tests {
class AbstractTest {

public:
    AbstractTest() {}
    virtual ~AbstractTest() {}
    virtual std::string name() = 0;
    virtual void test() = 0;
    virtual void clear() = 0;

    bool result() { return m_result; }
    std::vector<std::string>& resultDetails() { return m_resultDetails; }

protected:
    template <typename T>
    bool assertEqual(T& valueA, T& valueB)
    {
        bool assertationResult = valueA == valueB;
        if (!assertationResult) {
            m_resultDetails.push_back(
                "Assertation faied, " + oneCC::Utils::toString(valueA) + " != " + oneCC::Utils::toString(valueB));
        }
        m_result &= (assertationResult);
        return assertationResult;
    }

    bool assertTrue(bool value)
    {
        if (!value) {
            m_resultDetails.push_back("Assertation failed, " + oneCC::Utils::toString(value));
        }
        m_result &= value;
        return value;
    }

    bool assertFalse(bool value)
    {
        return assertTrue(!value);
    }

private:
    std::vector<std::string> m_resultDetails;
    bool m_result = true;
};
}