//
// Copyright (c) 2023-2023 Martin Moene
//
// https://github.com/martinmoene/indirect-value-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "indirect-value-main.t.hpp"

#define nsiv_PRESENT( x ) \
    std::cout << #x << ": " << (x) << "\n"

#define nsiv_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "indirect-value-lite version" "[.scope][.version]" )
{
    // nsiv_PRESENT( nsiv_lite_MAJOR );
    // nsiv_PRESENT( nsiv_lite_MINOR );
    // nsiv_PRESENT( nsiv_lite_PATCH );
    // nsiv_PRESENT( nsiv_lite_VERSION );
}

CASE( "indirect-value-lite configuration" "[.scope][.config]" )
{
    // nsiv_PRESENT( nsiv_HAVE_STD_SCOPE );
    // nsiv_PRESENT( nsiv_USES_STD_SCOPE );
    // nsiv_PRESENT( nsiv_SCOPE_DEFAULT );
    // nsiv_PRESENT( nsiv_SCOPE_NONSTD );
    // nsiv_PRESENT( nsiv_SCOPE_STD );
    // nsiv_PRESENT( nsiv_CONFIG_SELECT_SCOPE );
    // nsiv_PRESENT( nsiv_CONFIG_NO_EXTENSIONS );
    // nsiv_PRESENT( nsiv_CONFIG_NO_CONSTEXPR );
    // // nsiv_PRESENT( nsiv_CONFIG_NO_EXCEPTIONS );
    // nsiv_PRESENT( nsiv_USE_POST_CPP98_VERSION );
    // nsiv_PRESENT( nsiv_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    nsiv_PRESENT( __cplusplus );

#ifdef _MSVC_LANG
    nsiv_PRESENT( _MSVC_LANG );
#else
    nsiv_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
#if nsiv_USES_STD_SCOPE
    std::cout << "(Compiler version not available: using stdandard <scope>)\n";
#else
    // nsiv_PRESENT( nsiv_COMPILER_CLANG_VERSION );
    // nsiv_PRESENT( nsiv_COMPILER_GNUC_VERSION );
    // nsiv_PRESENT( nsiv_COMPILER_MSVC_VERSION );
#endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
#if nsiv_USES_STD_SCOPE
    std::cout << "(Presence of C++ language features not available: using stdandard <scope>)\n";
#else
    // nsiv_PRESENT( nsiv_HAVE_CONSTEXPR_11 );
    // nsiv_PRESENT( nsiv_HAVE_CONSTEXPR_14 );
    // nsiv_PRESENT( nsiv_HAVE_DECAY );
    // nsiv_PRESENT( nsiv_HAVE_DEDUCTION_GUIDES );
    // nsiv_PRESENT( nsiv_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
    // nsiv_PRESENT( nsiv_HAVE_NODISCARD );
    // nsiv_PRESENT( nsiv_HAVE_NOEXCEPT );
    // nsiv_PRESENT( nsiv_HAVE_IS_DEFAULT );
    // nsiv_PRESENT( nsiv_HAVE_IS_DELETE );
    // nsiv_PRESENT( nsiv_HAVE_STATIC_ASSERT );
#endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
#if nsiv_USES_STD_SCOPE
    std::cout << "(Presence of C++ library features not available: using stdandard <scope>)\n";
#else
    // nsiv_PRESENT( nsiv_HAVE_TYPE_TRAITS );
    // nsiv_PRESENT( nsiv_HAVE_TR1_TYPE_TRAITS );
    // nsiv_PRESENT( nsiv_HAVE_IS_SAME );
    // nsiv_PRESENT( nsiv_HAVE_IS_TRIVIAL );
    // nsiv_PRESENT( nsiv_HAVE_IS_TRIVIALLY_COPYABLE );
    // nsiv_PRESENT( nsiv_HAVE_IS_CONSTRUCTIBLE );
    // nsiv_PRESENT( nsiv_HAVE_IS_COPY_CONSTRUCTIBLE );
    // nsiv_PRESENT( nsiv_HAVE_IS_MOVE_CONSTRUCTIBLE );
    // nsiv_PRESENT( nsiv_HAVE_IS_NOTHROW_CONSTRUCTIBLE );
    // nsiv_PRESENT( nsiv_HAVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE );
    // nsiv_PRESENT( nsiv_HAVE_UNCAUGHT_EXCEPTIONS );
#endif

#if defined _HAS_CPP0X
    nsiv_PRESENT( _HAS_CPP0X );
#else
    nsiv_ABSENT(  _HAS_CPP0X );
#endif

#if defined __cpp_lib_experimental_scope
    nsiv_PRESENT( __cpp_lib_experimental_scope );
#else
    nsiv_ABSENT(  __cpp_lib_experimental_scope );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o indirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass
g++ -std=c++98 -I../include -o indirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass
g++ -std=c++03 -I../include -o indirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass
g++ -std=c++0x -I../include -o indirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass
g++ -std=c++11 -I../include -o indirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass
g++ -std=c++14 -I../include -o indirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass
g++ -std=c++17 -I../include -o indirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass

cl -EHsc -I../include -Feindirect-value-lite.t.exe indirect-value-main.t.cpp && indirect-value-lite.t.exe --pass
#endif

// end of file
