// example/01-basic.cpp

#include "nonstd/indirect_value.hpp"
#include <array>

using stdarr = std::array< int, 10 >;
using Vector = nonstd::indirect_value< stdarr >;

int main()
{
    Vector src = nonstd::make_indirect_value<stdarr>( stdarr( {0, 1, 2, 3, 4, 5, 6, 42} ) );

    Vector dst = src;

    return (*dst)[7];  // or: dst.value()[7]
}

// cl -nologo -EHsc -I../include 01-basic.cpp & 01-basic.exe
// g++ -std=c++17 -Wall -I../include -o 01-basic.exe 01-basic.cpp & 01-basic.exe
// clang -std=c++17 -Wall -I../include -o 01-basic.exe 01-basic.cpp & 01-basic.exe
// echo %ERRORLEVEL%
