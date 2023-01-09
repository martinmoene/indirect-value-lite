//
// Copyright (c) 2023-2023 Martin Moene
//
// https://github.com/martinmoene/indirect-value-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "indirect-value-main.t.hpp"

#include <iostream>

using namespace nonstd;

CASE( "indirect_value: Allows to default construct (empty)" )
{
    indirect_value<int> iv;

    EXPECT_NOT( iv );
}

CASE( "indirect_value: Allows to construct from pointer" )
{
    int * p = new int( 7 );
    indirect_value<int> iv( p );

    EXPECT(  iv      );
    EXPECT( *iv == 7 );
}

CASE( "indirect_value: Allows to copy-construct" )
{
    int * p = new int( 7 );
    indirect_value<int> iv0;
    indirect_value<int> iv1( p );

    indirect_value<int> iv2( iv0 );
    indirect_value<int> iv3( iv1 );

    EXPECT_NOT( iv2      );
    EXPECT(     iv3      );
    EXPECT(    *iv3 == 7 );
}

CASE( "indirect_value: Allows to move-construct" )
{
    int * p = new int( 7 );
    indirect_value<int> iv2( indirect_value<int>{   } );
    indirect_value<int> iv3( indirect_value<int>{ p } );

    EXPECT_NOT( iv2      );
    EXPECT(     iv3      );
    EXPECT(    *iv3 == 7 );
}

CASE( "indirect_value: Allows to copy-assign" )
{
    int * p = new int( 7 );
    indirect_value<int> iv0;
    indirect_value<int> iv1( p );
    indirect_value<int> iv2;

    iv2 = iv1;

    EXPECT(  iv2      );
    EXPECT( *iv2 == 7 );

    iv2 = iv0;

    EXPECT_NOT( iv2 );
}

CASE( "indirect_value: Allows to move-assign" )
{
    int * p = new int( 7 );
    indirect_value<int> iv0;
    indirect_value<int> iv1( p );
    indirect_value<int> iv2;

    iv2 = std::move( iv1 );

    EXPECT_NOT( iv1      );
    EXPECT(     iv2      );
    EXPECT(    *iv2 == 7 );

    iv2 = std::move( iv0 );

    EXPECT_NOT( iv2      );
}

// TODO: expand tests

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
