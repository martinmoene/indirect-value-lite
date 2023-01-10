//
// Copyright (c) 2023-2023 Martin Moene
//
// https://github.com/martinmoene/indirect-value-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST_INDIRECT_VALUE_LITE_H_INCLUDED
#define TEST_INDIRECT_VALUE_LITE_H_INCLUDED

#include nsiv_INDIRECT_VALUE_HEADER

// Compiler warning suppression for usage of lest:

#ifdef __clang__
# pragma clang diagnostic ignored "-Wstring-conversion"
# pragma clang diagnostic ignored "-Wunused-parameter"
# pragma clang diagnostic ignored "-Wunused-template"
# pragma clang diagnostic ignored "-Wunused-function"
# pragma clang diagnostic ignored "-Wunused-member-function"
#elif defined __GNUC__
# pragma GCC   diagnostic ignored "-Wunused-parameter"
# pragma GCC   diagnostic ignored "-Wunused-function"
#endif

#include <iosfwd>
namespace lest { template<typename T> std::ostream & operator<<( std::ostream & os, nonstd::indirect_value<T> const & iv ); }

#include "lest.hpp"

#define CASE( name ) lest_CASE( specification(), name )

// Attribute externally visible for -fwhole-program:

#if defined(__GNUC__) && !defined(__clang__)
# define scope_ATTRIBUTE_EXT_VIS  __attribute__((externally_visible))
#else
# define scope_ATTRIBUTE_EXT_VIS
#endif

extern lest::tests & specification() scope_ATTRIBUTE_EXT_VIS;

namespace lest {

    template< typename T >
    std::ostream & operator<<( std::ostream & os, nonstd::indirect_value<T> const & iv )
    {
        return os << "[indirect_value:" << bool(iv) << "]";
    }
}

#endif // TEST_INDIRECT_VALUE_LITE_H_INCLUDED

// end of file
