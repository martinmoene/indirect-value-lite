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

template< typename T >
void use( T const & /*arg*/) {}

static size_t copy_counter_call_count   = 0;
static size_t delete_counter_call_count = 0;

template< typename T >
class copy_counter
{
public:
    copy_counter() nsiv_noexcept
    {
        copy_counter_call_count = 0;
    }

    copy_counter( copy_counter const & )               = default;
    copy_counter( copy_counter      && ) nsiv_noexcept = default;
    copy_counter & operator=( copy_counter const & )               = default;
    copy_counter & operator=( copy_counter      && ) nsiv_noexcept = default;

    T * operator()( T const & rhs ) const
    {
        ++copy_counter_call_count;
        return nonstd::default_copy< T >().operator()( rhs );
    }
};

template< typename T >
class delete_counter
{
public:
    delete_counter() nsiv_noexcept
    {
        delete_counter_call_count = 0;
    }

    delete_counter( delete_counter const & )               = default;
    delete_counter( delete_counter      && ) nsiv_noexcept = default;
    delete_counter & operator=( delete_counter const & )               = default;
    delete_counter & operator=( delete_counter      && ) nsiv_noexcept = default;

    void operator()( T * rhs ) const
    {
        ++delete_counter_call_count;
        return std::default_delete< T >().operator()( rhs );
    }
};

// using counted_indirect_value = indirect_value<int, copy_counter<int>, delete_counter<int>>;

CASE( "indirect_value: Allows to default construct (empty)" )
{
    SETUP("scope")
    {
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv;

        // default disengaged:
        EXPECT_NOT( iv                         );
        EXPECT(     iv.operator->() == nullptr );

        EXPECT( copy_counter_call_count   == 0 );
        EXPECT( delete_counter_call_count == 0 );
    }

    EXPECT( copy_counter_call_count   == 0 );
    EXPECT( delete_counter_call_count == 0 );
}

CASE( "indirect_value: Allows to construct from pointer" )
{
    SETUP("scope")
    {
        const indirect_value<int, copy_counter<int>, delete_counter<int>> iv( new int( 7 ) );

        EXPECT(  iv      );
        EXPECT( *iv == 7 );

        EXPECT( copy_counter_call_count   == 0 );
        EXPECT( delete_counter_call_count == 0 );
    }

    EXPECT( copy_counter_call_count   == 0 );
    EXPECT( delete_counter_call_count == 1 );
}

CASE( "indirect_value: Allows to copy-construct" )
{
    SETUP("scope")
    {
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv0;
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv1( new int( 7 ) );

        indirect_value<int, copy_counter<int>, delete_counter<int>> iv2( iv0 );
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv3( iv1 );

        EXPECT_NOT( iv2      );
        EXPECT(     iv3      );
        EXPECT(    *iv3 == 7 );

        EXPECT( copy_counter_call_count   == 1 );
        EXPECT( delete_counter_call_count == 0 );
    }

    EXPECT( copy_counter_call_count   == 1 );
    EXPECT( delete_counter_call_count == 2 );
}

CASE( "indirect_value: Allows to move-construct" )
{
    SETUP("scope")
    {
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv2( indirect_value<int, copy_counter<int>, delete_counter<int>>{              } );
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv3( indirect_value<int, copy_counter<int>, delete_counter<int>>{ new int( 7 ) } );

        EXPECT_NOT( iv2      );
        EXPECT(     iv3      );
        EXPECT(    *iv3 == 7 );

        EXPECT( copy_counter_call_count   == 0 );
        EXPECT( delete_counter_call_count == 0 );
    }

    EXPECT( copy_counter_call_count   == 0 );
    EXPECT( delete_counter_call_count == 1 );
}

CASE( "indirect_value: Allows to copy-assign" )
{
    SETUP("scope")
    {
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv0;
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv1( new int( 7 ) );
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv2;

        iv2 = iv1;

        EXPECT(  iv2      );
        EXPECT( *iv2 == 7 );

        EXPECT( copy_counter_call_count   == 1 );
        EXPECT( delete_counter_call_count == 0 );

        iv2 = iv0;

        EXPECT_NOT( iv2 );

        EXPECT( copy_counter_call_count   == 1 );
        EXPECT( delete_counter_call_count == 1 );
    }

    EXPECT( copy_counter_call_count   == 1 );
    EXPECT( delete_counter_call_count == 2 );
}

CASE( "indirect_value: Allows to move-assign" )
{
    SETUP("scope")
    {
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv0;
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv1( new int( 7 ) );
        indirect_value<int, copy_counter<int>, delete_counter<int>> iv2;

        iv2 = std::move( iv1 );

        EXPECT_NOT( iv1      );
        EXPECT(     iv2      );
        EXPECT(    *iv2 == 7 );

        EXPECT( copy_counter_call_count   == 0 );
        EXPECT( delete_counter_call_count == 0 );

        iv2 = std::move( iv0 );

        EXPECT_NOT( iv2      );

        EXPECT( copy_counter_call_count   == 0 );
        EXPECT( delete_counter_call_count == 1 );
    }

    EXPECT( copy_counter_call_count   == 0 );
    EXPECT( delete_counter_call_count == 1 );
}

CASE( "indirect_value: Allows to swap (value)" )
{
    indirect_value<int> iv3( new int( 3 ) );
    indirect_value<int> iv7( new int( 7 ) );

    iv3.swap( iv7 );

    EXPECT( *iv3 == 7 );
    EXPECT( *iv7 == 3 );
}

// TODO: indirect_value: Allows to swap (copier)

CASE( "indirect_value: Allows to swap (copier)" " [TODO]" )
{
}

// TODO: indirect_value: Allows to swap (deleter)

CASE( "indirect_value: Allows to swap (deleter)" " [TODO]" )
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
    const indirect_value<S> ivs7( new S );

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

CASE( "indirect_value: No throw of exception on valid value access (value() &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( iv7.value() );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: No throw of exception on valid value access(value() const &)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( iv7.value() );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: No throw of exception on valid value access(value() &&)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( std::move(iv7).value() );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: No throw of exception on valid value access(value() const &&)" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( std::move(iv7).value() );
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

// TODO: indirect_value: Allows to obtain copier (get_copier() &)

CASE( "indirect_value: Allows to obtain copier (get_copier() &)" " [TODO]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS
    indirect_value<int> iv;

    auto copier = iv.get_copier();

    use( copier );
#else
    EXPECT( !!"indirect_value: get_copier() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

// TODO: indirect_value: Allows to obtain copier (get_copier() const &)

CASE( "indirect_value: Allows to obtain copier (get_copier() const &)" " [TODO]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS
    const indirect_value<int> iv;

    auto copier = iv.get_copier();

    use( copier );
#else
    EXPECT( !!"indirect_value: get_copier() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

// TODO: indirect_value: Allows to obtain copier (get_deleter() &)

CASE( "indirect_value: Allows to obtain deleter (get_deleter() &)" " [TODO]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS
    indirect_value<int> iv;

    auto deleter = iv.get_deleter();

    use( deleter );
#else
    EXPECT( !!"indirect_value: get_deleter() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

// TODO: indirect_value: Allows to obtain copier (get_deleter() const &)

CASE( "indirect_value: Allows to obtain deleter (get_deleter() const &)" " [TODO]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS
    const indirect_value<int> iv;

    auto deleter = iv.get_deleter();

    use( deleter );
#else
    EXPECT( !!"indirect_value: get_deleter() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

CASE( "make_indirect_value(): Allows to in-place construct an indirect value from parameters" )
{
    auto iv7 = make_indirect_value<int>(7);

    EXPECT( *iv7 == 7 );
}

struct Composite
{
    Composite( int x )
    : m_x( x ) {}

    Composite( Composite const & ) = default;

    int m_x;
};

// TODO: allocate_indirect_value(): Allows to in-place construct an indirect value from parameters, with given allocator

CASE( "allocate_indirect_value(): Allows to in-place construct an indirect value from parameters, with given allocator" " [TODO]" )
{
    // std::allocator<int> alloc;
    // int value = 7;
    // auto iv7 = allocate_indirect_value<Composite>( std::allocator_arg_t{}, alloc, value );

    // EXPECT( *iv7 == 7 );
}

CASE( "swap(): Allows to swap" )
{
    indirect_value<int> iv3( new int( 3 ) );
    indirect_value<int> iv7( new int( 7 ) );

    swap( iv3, iv7 );

    EXPECT( *iv3 == 7 );
    EXPECT( *iv7 == 3 );
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

CASE( "relational operators: Allows to compare indirect_value with nullptr" " [TODO]" )
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

// TODO: std::hash: Allows to

CASE( "std::hash: Allows to ..." " [TODO]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_STD_HASH

#else
    EXPECT( !!"std::hash: std::hash specialisation is not available (nsiv_CONFIG_NO_EXTENSION_STD_HASH=1)" );
#endif
}

// TODO: expand tests (taken from https://github.com/jbcoe/indirect_value):
//
// - [x] "Ensure that indirect_value uses the minimum space requirements"
// - [ ] "Default construction for indirect_value", "[constructor.default]"
// - [ ] "Element wise initialisation construction for indirect_value"
// - [ ] "Copy construction for indirect_value of a primitive type"
// - [ ] "Copy assignment for indirect_value of a primitive type"
// - [ ] "Move construction for indirect_value of a primitive type"
// - [ ] "Move assignment for indirect_value of a primitive type"
// - [ ] "Operator bool for indirect_value", "[operator.bool]"
// - [ ] "Swap overload for indirect_value", "[swap.primitive]"
// - [ ] "Noexcept of observers", "[TODO]"
// - [ ] "Ref- and const-qualifier of observers", "[TODO]"
// - [ ] "Test properties of bad_indirect_value_access", "[TODO]"
// - [ ] "Calling value on empty indirect_value will throw"
// - [ ] "Calling value on an enganged indirect_value will not throw"
// - [ ] "get_copier returns modifiable lvalue reference", "[TODO]"
// - [ ] "get_deleter returns modifiable lvalue reference", "[TODO]"
// - [ ] "Stats of copy and delete type", "[TODO]"
// - [ ] "Protection against reentrancy", "[TODO]"
// - [ ] "Self assign an indirect_value", "[TODO]"
// - [ ] "Throwing copy constructor", "[TODO]"
// - [ ] "Use source copier when copying", "[TODO]"
// - [ ] "Working with an incomplete type", "[completeness.of.t]"
// - [ ] "Allocator used to construct with allocate_indirect_value "
// - [ ] "Relational operators between two indirect_values", "[TODO]"
// - [ ] "Relational operators between two indirect_values of different type"
// - [ ] "Relational operators between an indirect_value and nullptr"
// - [ ] "Relational operators between indirect_value and value_type"
// - [ ] "Relational operators between indirect_value and value_type of different type"
// - [ ] "Relational operators between indirect_value and value_type of non-equality-comparable type"
// - [ ] "Hash for indirect_value", "[TODO]"

CASE( "indirect_value: Ensure using minimum space requirements" "[TODO]" )
{
    static_assert(
        sizeof(indirect_value<int>) == sizeof(int *)
        , "expect size of pointer to datatype" );

    // Same type for copy and delete:
    struct CopyDeleteHybrid
    {
        void  operator()( int * p ) { delete p; }
        int * operator()( const int & s ) { return new int( s ); }
    };

    static_assert(
        sizeof(indirect_value< int, CopyDeleteHybrid, CopyDeleteHybrid >) == sizeof(int *)
        , "expect size of pointer to datatype" );
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
