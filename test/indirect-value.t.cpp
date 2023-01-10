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
    const indirect_value<int> iv( new int( 7 ) );

    EXPECT(  iv      );
    EXPECT( *iv == 7 );
}

CASE( "indirect_value: Allows to copy-construct" )
{
    indirect_value<int> iv0;
    indirect_value<int> iv1( new int( 7 ) );

    indirect_value<int> iv2( iv0 );
    indirect_value<int> iv3( iv1 );

    EXPECT_NOT( iv2      );
    EXPECT(     iv3      );
    EXPECT(    *iv3 == 7 );
}

CASE( "indirect_value: Allows to move-construct" )
{
    indirect_value<int> iv2( indirect_value<int>{              } );
    indirect_value<int> iv3( indirect_value<int>{ new int( 7 ) } );

    EXPECT_NOT( iv2      );
    EXPECT(     iv3      );
    EXPECT(    *iv3 == 7 );
}

CASE( "indirect_value: Allows to copy-assign" )
{
    indirect_value<int> iv0;
    indirect_value<int> iv1( new int( 7 ) );
    indirect_value<int> iv2;

    iv2 = iv1;

    EXPECT(  iv2      );
    EXPECT( *iv2 == 7 );

    iv2 = iv0;

    EXPECT_NOT( iv2 );
}

CASE( "indirect_value: Allows to move-assign" )
{
    indirect_value<int> iv0;
    indirect_value<int> iv1( new int( 7 ) );
    indirect_value<int> iv2;

    iv2 = std::move( iv1 );

    EXPECT_NOT( iv1      );
    EXPECT(     iv2      );
    EXPECT(    *iv2 == 7 );

    iv2 = std::move( iv0 );

    EXPECT_NOT( iv2      );
}

CASE( "indirect_value: Allows to swap (value)" )
{
    indirect_value<int> iv3( new int( 3 ) );
    indirect_value<int> iv7( new int( 7 ) );

    iv3.swap( iv7 );

    EXPECT( *iv3 == 7 );
    EXPECT( *iv7 == 3 );
}

CASE( "indirect_value: Allows to swap (copier)" )
{
}

CASE( "indirect_value: Allows to swap (deleter)" )
{
}

CASE( "indirect_value: Allows to check if engaged, has_value()" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv;
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NOT(  iv.has_value() );
    EXPECT(     iv7.has_value() );
#else
    EXPECT( !!"indirect_value: has_value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

struct S { int x = 7; };

CASE( "indirect_value: Allows to obtain value (op->)" )
{
    indirect_value<S> ivs7( new S );

    EXPECT( ivs7->x == 7 );
}

CASE( "indirect_value: Allows to obtain value (op-> const)" )
{
    indirect_value<S> ivs7( new S );

    EXPECT( ivs7->x == 7 );
}

CASE( "indirect_value: Allows to obtain value (op* &)" )
{
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT( *iv7 == 7 );
}

CASE( "indirect_value: Allows to obtain value (op* const &)" )
{
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT( *iv7 == 7 );
}

CASE( "indirect_value: Allows to obtain value (op* &&)" )
{
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT( *std::move(iv7) == 7 );
}

CASE( "indirect_value: Allows to obtain value (op* const &&)" )
{
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT( *std::move(iv7) == 7 );
}

CASE( "indirect_value: Allows to obtain value (value() &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT( iv7.value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain value (value() const &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT( iv7.value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain value (value() &&)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT( std::move(iv7).value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain value (value() const &&)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT( std::move(iv7).value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv;

    EXPECT_THROWS_AS( iv.value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() const &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv;

    EXPECT_THROWS_AS( iv.value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() &&)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv;

    EXPECT_THROWS_AS( std::move(iv).value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() const &&)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv;

    EXPECT_THROWS_AS( std::move(iv).value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain copier (get_copier() &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS

#else
    EXPECT( !!"indirect_value: get_copier() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain copier (get_copier() const &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS

#else
    EXPECT( !!"indirect_value: get_copier() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain deleter (get_deleter() &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS

#else
    EXPECT( !!"indirect_value: get_deleter() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain deleter (get_deleter() const &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS

#else
    EXPECT( !!"indirect_value: get_deleter() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

CASE( "make_indirect_value(): Allows to in-place construct an indirect value from parameters" )
{
}

CASE( "allocate_indirect_value(): Allows to in-place construct an indirect value from parameters, with given allocator" )
{
}

CASE( "swap(): Allows to swap" )
{
}

CASE( "relational operators: Allows to compare indirect_value-s" )
{
#if !nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS

    indirect_value<int> iv3( new int( 3 ) );
    indirect_value<int> iv7( new int( 7 ) );
    indirect_value<int> iv9( new int( 9 ) );

    EXPECT( (iv7 == iv7) );
    EXPECT( (iv7 == iv7) );

    EXPECT( (iv7 != iv3) );
    EXPECT( (iv3 != iv7) );

    EXPECT( (iv7 <  iv9) );
    EXPECT( (iv3 <  iv7) );

    EXPECT( (iv7 <= iv9) );
    EXPECT( (iv3 <= iv7) );

    EXPECT( (iv7 >  iv3) );
    EXPECT( (iv9 >  iv7) );

    EXPECT( (iv7 >= iv3) );
    EXPECT( (iv9 >= iv7) );
#else
    EXPECT( !!"relational operators: comparison is not available (nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS=1)" );
#endif
}

// TODO: _enable_if_comparable_with_equal etc. do not (yet) allow for the likes of op==(indirect_value, nullptr_t).

CASE( "relational operators: Allows to compare indirect_value with nullptr" )
{
#if !nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS
    indirect_value<int> iv7( new int( 7 ) );

    // EXPECT( (    iv7 == nullptr) );
    // EXPECT( (nullptr == iv7) );

    // EXPECT( (    iv7 != nullptr) );
    // EXPECT( (nullptr != iv7) );

    // EXPECT( (    iv7 < nullptr) );
    // EXPECT( (nullptr < iv7) );

    // EXPECT( (    iv7 <= nullptr) );
    // EXPECT( (nullptr <= iv7) );

    // EXPECT( (    iv7 >  nullptr) );
    // EXPECT( (nullptr >  iv7) );

    // EXPECT( (    iv7 >= nullptr) );
    // EXPECT( (nullptr >= iv7) );

    // EXPECT_NOT( (iv7 ==   nullptr) );
    // EXPECT_NOT( (  nullptr == iv7) );
#else
    EXPECT( !!"relational operators: comparison is not available (nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS=1)" );
#endif
}

CASE( "relational operators: Allows to compare indirect_value with value convertible to its value_type" )
{
#if !nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS

    indirect_value<int> iv7( new int( 7 ) );

    EXPECT( (iv7 ==   7) );
    EXPECT( (  7 == iv7) );

    EXPECT( (iv7 !=   3) );
    EXPECT( (  3 != iv7) );

    EXPECT( (iv7 <    9) );
    EXPECT( (  3 <  iv7) );

    EXPECT( (iv7 <=   9) );
    EXPECT( (  3 <= iv7) );

    EXPECT( (iv7 >    3) );
    EXPECT( (  9 >  iv7) );

    EXPECT( (iv7 >=   3) );
    EXPECT( (  9 >= iv7) );

    EXPECT_NOT( (iv7 ==   3) );
    EXPECT_NOT( (  3 == iv7) );
#else
    EXPECT( !!"relational operators: comparison is not available (nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS=1)" );
#endif
}

CASE( "std::hash: Allows to ..." )
{
#if !nsiv_CONFIG_NO_EXTENSION_STD_HASH

#else
    EXPECT( !!"std::hash: std::hash specialisation is not available (nsiv_CONFIG_NO_EXTENSION_STD_HASH=1)" );
#endif
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
