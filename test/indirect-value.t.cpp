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

CASE( "indirect_value: Allows to in-place construct from arguments" )
{
    SETUP("scope")
    {
        const indirect_value<int, copy_counter<int>, delete_counter<int>> iv( nonstd_lite_in_place(int), 7 );

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

CASE( "indirect_value: Allows to check if engaged, has_value()" " [extension]" )
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

CASE( "indirect_value: Allows to obtain value (value() &)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT( iv7.value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain value (value() const &)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT( iv7.value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain value (value() &&)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT( std::move(iv7).value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Allows to obtain value (value() const &&)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT( std::move(iv7).value() == 7 );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: No throw of exception on valid value access (value() &)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( iv7.value() );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: No throw of exception on valid value access(value() const &)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( iv7.value() );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: No throw of exception on valid value access(value() &&)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( std::move(iv7).value() );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: No throw of exception on valid value access(value() const &&)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv7( new int( 7 ) );

    EXPECT_NO_THROW( std::move(iv7).value() );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() &)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv;

    EXPECT_THROWS_AS( iv.value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() const &)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv;

    EXPECT_THROWS_AS( iv.value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() &&)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    indirect_value<int> iv;

    EXPECT_THROWS_AS( std::move(iv).value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Throws on bad value access (value() const &&)" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    const indirect_value<int> iv;

    EXPECT_THROWS_AS( std::move(iv).value(), bad_indirect_value_access );
#else
    EXPECT( !!"indirect_value: value() is not available (nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS=1)" );
#endif
}

// TODO: indirect_value: Allows to obtain copier (get_copier() &)

CASE( "indirect_value: Allows to obtain copier (get_copier() &)" " [extension][TODO]" )
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

CASE( "indirect_value: Allows to obtain copier (get_copier() const &)" " [extension][TODO]" )
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

CASE( "indirect_value: Allows to obtain deleter (get_deleter() &)" " [extension][TODO]" )
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

CASE( "indirect_value: Allows to obtain deleter (get_deleter() const &)" " [extension][TODO]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS
    const indirect_value<int> iv;

    auto deleter = iv.get_deleter();

    use( deleter );
#else
    EXPECT( !!"indirect_value: get_deleter() is not available (nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS=1)" );
#endif
}

CASE( "indirect_value: Ensure using minimum space requirements" "[TODO]" )
{
    // static_assert(
    //     sizeof(indirect_value<int>) == sizeof(int *)
    //     , "expect size of pointer to datatype" );
    EXPECT( sizeof(indirect_value<int>) == sizeof(int *) );

    // Same type for copy and delete:
    struct CopyDeleteHybrid
    {
        void  operator()( int * p ) { delete p; }
        int * operator()( const int & s ) { return new int( s ); }
    };

    // static_assert(
    //     sizeof(indirect_value< int, CopyDeleteHybrid, CopyDeleteHybrid >) == sizeof(int *)
    //     , "expect size of pointer to datatype" );
    EXPECT( sizeof(indirect_value< int, CopyDeleteHybrid, CopyDeleteHybrid >) == sizeof(int *) );
}

// Algorithms:

CASE( "make_indirect_value(): Allows to in-place construct an indirect value from parameters" )
{
    auto iv7 = make_indirect_value<int>(7);

    EXPECT( *iv7 == 7 );
}

namespace {

template< typename T >
struct tracking_allocator
{
    unsigned * alloc_counter;
    unsigned * dealloc_counter;

    explicit tracking_allocator( unsigned * a, unsigned * d ) noexcept
        : alloc_counter( a )
        , dealloc_counter( d )
    {
    }

    template < typename U >
    tracking_allocator( const tracking_allocator< U > & other )
        : alloc_counter( other.alloc_counter )
        , dealloc_counter( other.dealloc_counter )
    {
    }

    using value_type = T;

    template < typename Other >
    struct rebind
    {
        using other = tracking_allocator< Other >;
    };

    nsiv_constexpr14 T * allocate( std::size_t n )
    {
        ++*alloc_counter;
        std::allocator< T > default_allocator{};  // LCOV_EXCL_LINE
        return default_allocator.allocate( n );
    }

    nsiv_constexpr20 void deallocate( T * p, std::size_t n )
    {
        ++*dealloc_counter;
        std::allocator< T > default_allocator{};
        default_allocator.deallocate( p, n );
    }
};

struct CompositeType
{
    int m_value = 0;

    CompositeType() { ++object_count; }

    CompositeType( const CompositeType & d )
    {
        m_value = d.m_value;
        ++object_count;
    }

    CompositeType( int v )
        : m_value( v )
    {
        ++object_count;
    }

    ~CompositeType() { --object_count; }

    int  value() const { return m_value; }
    void set_value( int i ) { m_value = i; }

    static size_t object_count;
};

size_t CompositeType::object_count = 0;
} // anonymous namespace

CASE( "allocate_indirect_value(): Allows to in-place construct an indirect value from parameters, with given allocator" )
{
    SETUP( "" ) {
        unsigned allocs   = 0;
        unsigned deallocs = 0;
        tracking_allocator<int> alloc( &allocs, &deallocs );

    SECTION( "allocate, deallocate on destruction" ) {
        {
            auto ct = allocate_indirect_value<CompositeType>( std::allocator_arg_t{}, alloc, 7 );

            EXPECT( ct->value() == 7 );
            EXPECT( allocs   == 1 );
            EXPECT( deallocs == 0 );

            // ct.~indirect_value();
        }
        EXPECT( allocs   == 1 );
        EXPECT( deallocs == 1 );
    }
    SECTION( "allocate, deallocate on throw" ) {
        struct ThrowOnConstruct
        {
            ThrowOnConstruct() { throw "default constructor throws"; }
        };

        // Seems to abort on gcc/clang: more than one exception in flight?
        // EXPECT_THROWS( allocate_indirect_value<ThrowOnConstruct>( std::allocator_arg_t{}, alloc ) );

        // EXPECT( allocs   == 1 );
        // EXPECT( deallocs == 1 );
    }}
}

CASE( "swap(): Allows to swap" )
{
    indirect_value<int> iv3( new int( 3 ) );
    indirect_value<int> iv7( new int( 7 ) );

    swap( iv3, iv7 );

    EXPECT( *iv3 == 7 );
    EXPECT( *iv7 == 3 );
}

CASE( "relational operators: Allows to compare indirect_value-s" " [extension]" )
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

CASE( "relational operators: Allows to compare indirect_value with nullptr" " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS
    indirect_value<int> iv0;
    indirect_value<int> iv7( new int( 7 ) );

    EXPECT(     (    iv0 == nullptr) );
    EXPECT(     (nullptr == iv0    ) );

    EXPECT(     (    iv7 != nullptr) );
    EXPECT(     (nullptr != iv7    ) );

    EXPECT_NOT( (    iv7 <  nullptr) );
    EXPECT(     (nullptr <  iv7    ) );

    EXPECT_NOT( (    iv7 <= nullptr) );
    EXPECT(     (nullptr <= iv7    ) );

    EXPECT(     (    iv7 >  nullptr) );
    EXPECT_NOT( (nullptr >  iv7    ) );

    EXPECT(     (    iv7 >= nullptr) );
    EXPECT_NOT( (nullptr >= iv7    ) );

    EXPECT_NOT( (    iv7 == nullptr) );
    EXPECT_NOT( (nullptr == iv7    ) );
#else
    EXPECT( !!"relational operators: comparison is not available (nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS=1)" );
#endif
}

CASE( "relational operators: Allows to compare indirect_value with value convertible to its value_type" " [extension]" )
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

// std::hash specialisation:

namespace std17 {
#if nsiv_HAVE_VOID_T
    using ::std::void_t;
#else
    using ::nonstd::iv::std17::void_t;
#endif
}

template < typename T, typename = void >
struct IsHashable : std::false_type{};

template < typename T >
struct IsHashable< T, std17::void_t< decltype( std::hash<T>{}( std::declval<const T &>() ) ) > > : std::true_type
{
    enum { IsNoexcept = noexcept( std::hash<T>{}( std::declval<const T &>() ) ) };
};

struct ProvidesNoHash{};
struct ProvidesThrowingHash{};

namespace std {
template<>
struct hash< ProvidesThrowingHash >
{
    size_t operator()( const ProvidesThrowingHash & ) const { return 0; }
};
}  // namespace std

CASE( "std::hash: Allows to hash an indirect_value"  " [extension]" )
{
#if !nsiv_CONFIG_NO_EXTENSION_STD_HASH
    // The hash value for empty indirect_value is zero:
    {
        const indirect_value<int> empty;

        EXPECT( std::hash<indirect_value<int>>{}(empty) == 0 );
        EXPECT( IsHashable<int>::IsNoexcept );                  // compile-time
        EXPECT( IsHashable<indirect_value<int>>::IsNoexcept );  // compile-time
    }

    // Equal hash value for same value and underlying indirect value:
    {
        const indirect_value<int> iv( nonstd_lite_in_place(int), 7 );

        EXPECT( std::hash<int>{}(*iv) == std::hash<indirect_value<int>>{}(iv) );
    }

    // A type which is not hashable:
    {
        EXPECT_NOT( IsHashable<                 ProvidesNoHash  >::value );
        EXPECT_NOT( IsHashable< indirect_value< ProvidesNoHash >>::value );
    }

    // A type which is hashable and std::hash throws:
    {
        EXPECT(     IsHashable<                 ProvidesThrowingHash  >::value      );
        EXPECT(     IsHashable< indirect_value< ProvidesThrowingHash >>::value      );
        EXPECT_NOT( IsHashable<                 ProvidesThrowingHash  >::IsNoexcept );
        EXPECT_NOT( IsHashable< indirect_value< ProvidesThrowingHash >>::IsNoexcept );
    }
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
// - [x] "Allocator used to construct with allocate_indirect_value "
// - [x] "Relational operators between two indirect_values", "[TODO]"
// - [x] "Relational operators between two indirect_values of different type"
// - [x] "Relational operators between an indirect_value and nullptr"
// - [x] "Relational operators between indirect_value and value_type"
// - [x] "Relational operators between indirect_value and value_type of different type"
// - [x] "Relational operators between indirect_value and value_type of non-equality-comparable type"
// - [x] "Hash for indirect_value", "[TODO]"

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
