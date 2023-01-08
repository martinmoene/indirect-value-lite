//
// Copyright (c) 2023-2023 Martin Moene
//
// https://github.com/martinmoene/indirect-value-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "indirect-value-main.t.hpp"

#include <functional>
#include <iostream>

CASE( "Default Construct" )
{
    nonstd::indirect_value<int> iv;
}

CASE( "tweak header: reads tweak header if supported " "[tweak]" )
{
#if nsiv_HAVE_TWEAK_HEADER
    EXPECT( INDIRECT_VALUE_TWEAK_VALUE == 42 );
#else
    EXPECT( !!"Tweak header is not available (nsiv_HAVE_TWEAK_HEADER: 0)." );
#endif
}

// Issues:

// end of file
