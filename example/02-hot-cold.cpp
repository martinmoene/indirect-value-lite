// example/02-hot-cold.cpp

#include "nonstd/indirect_value.hpp"
#include <algorithm>
#include <vector>

struct SmallData { int x = 7; bool active() const {return true;} };
struct LargeData { int a[1000]; };

struct Element
{
    SmallData                         frequently_accessed_data;
    nonstd::indirect_value<LargeData> infrequently_accessed_data;
};

int main()
{
    std::vector<Element> elements(3);

    auto active = std::find_if(
        elements.begin(),
        elements.end(),
        [](const auto& e)
        {
            return e.frequently_accessed_data.active();
        });

    return active != std::end(elements);
}

// cl -nologo -EHsc -I../include 02-hot-cold.cpp & 02-hot-cold.exe
// echo %ERRORLEVEL%
