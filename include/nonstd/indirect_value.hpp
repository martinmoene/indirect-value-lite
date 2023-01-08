//
// Copyright (c) 2023-2023 Martin Moene
//
// https://github.com/martinmoene/indirect-value-lite (p1950)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef NONSTD_INDIRECT_VALUE_LITE_HPP
#define NONSTD_INDIRECT_VALUE_LITE_HPP

#define indirect_value_MAJOR  0
#define indirect_value_MINOR  0
#define indirect_value_PATCH  0

#define indirect_value_VERSION  nsiv_STRINGIFY(indirect_value_MAJOR) "." nsiv_STRINGIFY(indirect_value_MINOR) "." nsiv_STRINGIFY(indirect_value_PATCH)

#define nsiv_STRINGIFY(  x )  nsiv_STRINGIFY_( x )
#define nsiv_STRINGIFY_( x )  #x

// indirect-value-lite configuration:

#define nsiv_INDIRECT_VALUE_DEFAULT  0
#define nsiv_INDIRECT_VALUE_NONSTD   1
#define nsiv_INDIRECT_VALUE_STD      2

// tweak header support:

#ifdef __has_include
# if __has_include(<nonstd/indirect_value.tweak.hpp>)
#  include <nonstd/indirect_value.tweak.hpp>
# endif
#define nsiv_HAVE_TWEAK_HEADER  1
#else
#define nsiv_HAVE_TWEAK_HEADER  0
//# pragma message("indirect_value.hpp: Note: Tweak header not supported.")
#endif

// scope selection and configuration:

#if !defined( nsiv_CONFIG_SELECT_INDIRECT_VALUE )
# define nsiv_CONFIG_SELECT_INDIRECT_VALUE  ( nsiv_HAVE_STD_INDIRECT_VALUE ? nsiv_INDIRECT_VALUE_STD : nsiv_INDIRECT_VALUE_NONSTD )
#endif

#if !defined( nsiv_CONFIG_NO_EXTENSIONS )
# define nsiv_CONFIG_NO_EXTENSIONS  0
#endif

// #if !defined( nsiv_CONFIG_NO_CONSTEXPR )
// # define nsiv_CONFIG_NO_CONSTEXPR  (nsiv_CONFIG_NO_EXTENSIONS || !nsiv_CPP20_OR_GREATER)
// #endif

// C++ language version detection (C++23 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   nsiv_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define nsiv_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define nsiv_CPLUSPLUS  __cplusplus
# endif
#endif

#define nsiv_CPP98_OR_GREATER  ( nsiv_CPLUSPLUS >= 199711L )
#define nsiv_CPP11_OR_GREATER  ( nsiv_CPLUSPLUS >= 201103L )
#define nsiv_CPP14_OR_GREATER  ( nsiv_CPLUSPLUS >= 201402L )
#define nsiv_CPP17_OR_GREATER  ( nsiv_CPLUSPLUS >= 201703L )
#define nsiv_CPP20_OR_GREATER  ( nsiv_CPLUSPLUS >= 202002L )
#define nsiv_CPP23_OR_GREATER  ( nsiv_CPLUSPLUS >= 202300L )

// // Use C++yy <???> if available and requested:
// // Note: __cpp_lib_experimental_???: a value of at least yyyynn indicates that the indirect_value is supported

#define nsiv_HAVE_STD_INDIRECT_VALUE  0

// #if nsiv_CPP20_OR_GREATER && defined(__has_include )
// # if   __has_include( <???> )
// #  define nsiv_HAVE_STD_INDIRECT_VALUE  1
// # elif __has_include( <experimental/???> )
// #  define nsiv_HAVE_STD_INDIRECT_VALUE  1
// # else
// #  define nsiv_HAVE_STD_INDIRECT_VALUE  0
// # endif
// #else
// # define  nsiv_HAVE_STD_INDIRECT_VALUE  0
// #endif

#define  nsiv_USES_STD_INDIRECT_VALUE  ( (nsiv_CONFIG_SELECT_INDIRECT_VALUE == nsiv_INDIRECT_VALUE_STD) || ((nsiv_CONFIG_SELECT_INDIRECT_VALUE == nsiv_INDIRECT_VALUE_DEFAULT) && nsiv_HAVE_STD_INDIRECT_VALUE) )

//
// in_place: code duplicated in any-lite, expected-lite, indirect_value, optional-lite, value-ptr-lite, variant-lite:
//

#ifndef nonstd_lite_HAVE_IN_PLACE_TYPES
#define nonstd_lite_HAVE_IN_PLACE_TYPES  1

// C++17 std::in_place in <utility>:

#if nsiv_CPP17_OR_GREATER

#include <utility>

namespace nonstd {

using std::in_place;
using std::in_place_type;
using std::in_place_index;
using std::in_place_t;
using std::in_place_type_t;
using std::in_place_index_t;

#define nonstd_lite_in_place_t(      T)  std::in_place_t
#define nonstd_lite_in_place_type_t( T)  std::in_place_type_t<T>
#define nonstd_lite_in_place_index_t(K)  std::in_place_index_t<K>

#define nonstd_lite_in_place(      T)    std::in_place_t{}
#define nonstd_lite_in_place_type( T)    std::in_place_type_t<T>{}
#define nonstd_lite_in_place_index(K)    std::in_place_index_t<K>{}

} // namespace nonstd

#else // nsiv_CPP17_OR_GREATER

#include <cstddef>

namespace nonstd {
namespace detail {

template< class T >
struct in_place_type_tag {};

template< std::size_t K >
struct in_place_index_tag {};

} // namespace detail

struct in_place_t {};

template< class T >
inline in_place_t in_place( detail::in_place_type_tag<T> /*unused*/ = detail::in_place_type_tag<T>() )
{
    return in_place_t();
}

template< std::size_t K >
inline in_place_t in_place( detail::in_place_index_tag<K> /*unused*/ = detail::in_place_index_tag<K>() )
{
    return in_place_t();
}

template< class T >
inline in_place_t in_place_type( detail::in_place_type_tag<T> /*unused*/ = detail::in_place_type_tag<T>() )
{
    return in_place_t();
}

template< std::size_t K >
inline in_place_t in_place_index( detail::in_place_index_tag<K> /*unused*/ = detail::in_place_index_tag<K>() )
{
    return in_place_t();
}

// mimic templated typedef:

#define nonstd_lite_in_place_t(      T)  nonstd::in_place_t(&)( nonstd::detail::in_place_type_tag<T>  )
#define nonstd_lite_in_place_type_t( T)  nonstd::in_place_t(&)( nonstd::detail::in_place_type_tag<T>  )
#define nonstd_lite_in_place_index_t(K)  nonstd::in_place_t(&)( nonstd::detail::in_place_index_tag<K> )

#define nonstd_lite_in_place(      T)    nonstd::in_place_type<T>
#define nonstd_lite_in_place_type( T)    nonstd::in_place_type<T>
#define nonstd_lite_in_place_index(K)    nonstd::in_place_index<K>

} // namespace nonstd

#endif // nsiv_CPP17_OR_GREATER
#endif // nonstd_lite_HAVE_IN_PLACE_TYPES

//
// Using std::indirect_value, or nonstd::indirect_value:
//

#if nsiv_USES_STD_INDIRECT_VALUE
// std::indirect_value is non-existent
#else // nsiv_USES_STD_INDIRECT_VALUE

// half-open range [lo..hi):
#define nsiv_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Compiler versions:
//
// MSVC++  6.0  _MSC_VER == 1200  nsiv_COMPILER_MSVC_VERSION ==  60  (Visual Studio 6.0)
// MSVC++  7.0  _MSC_VER == 1300  nsiv_COMPILER_MSVC_VERSION ==  70  (Visual Studio .NET 2002)
// MSVC++  7.1  _MSC_VER == 1310  nsiv_COMPILER_MSVC_VERSION ==  71  (Visual Studio .NET 2003)
// MSVC++  8.0  _MSC_VER == 1400  nsiv_COMPILER_MSVC_VERSION ==  80  (Visual Studio 2005)
// MSVC++  9.0  _MSC_VER == 1500  nsiv_COMPILER_MSVC_VERSION ==  90  (Visual Studio 2008)
// MSVC++ 10.0  _MSC_VER == 1600  nsiv_COMPILER_MSVC_VERSION == 100  (Visual Studio 2010)
// MSVC++ 11.0  _MSC_VER == 1700  nsiv_COMPILER_MSVC_VERSION == 110  (Visual Studio 2012)
// MSVC++ 12.0  _MSC_VER == 1800  nsiv_COMPILER_MSVC_VERSION == 120  (Visual Studio 2013)
// MSVC++ 14.0  _MSC_VER == 1900  nsiv_COMPILER_MSVC_VERSION == 140  (Visual Studio 2015)
// MSVC++ 14.1  _MSC_VER >= 1910  nsiv_COMPILER_MSVC_VERSION == 141  (Visual Studio 2017)
// MSVC++ 14.2  _MSC_VER >= 1920  nsiv_COMPILER_MSVC_VERSION == 142  (Visual Studio 2019)

#if defined(_MSC_VER ) && !defined(__clang__)
# define nsiv_COMPILER_MSVC_VER      (_MSC_VER )
# define nsiv_COMPILER_MSVC_VERSION  (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define nsiv_COMPILER_MSVC_VER      0
# define nsiv_COMPILER_MSVC_VERSION  0
#endif

// Courtesy of https://github.com/gsl-lite/gsl-lite
// AppleClang  7.0.0  __apple_build_version__ ==  7000172  nsiv_COMPILER_APPLECLANG_VERSION ==  700  (Xcode 7.0, 7.0.1)          (LLVM 3.7.0)
// AppleClang  7.0.0  __apple_build_version__ ==  7000176  nsiv_COMPILER_APPLECLANG_VERSION ==  700  (Xcode 7.1)                 (LLVM 3.7.0)
// AppleClang  7.0.2  __apple_build_version__ ==  7000181  nsiv_COMPILER_APPLECLANG_VERSION ==  702  (Xcode 7.2, 7.2.1)          (LLVM 3.7.0)
// AppleClang  7.3.0  __apple_build_version__ ==  7030029  nsiv_COMPILER_APPLECLANG_VERSION ==  730  (Xcode 7.3)                 (LLVM 3.8.0)
// AppleClang  7.3.0  __apple_build_version__ ==  7030031  nsiv_COMPILER_APPLECLANG_VERSION ==  730  (Xcode 7.3.1)               (LLVM 3.8.0)
// AppleClang  8.0.0  __apple_build_version__ ==  8000038  nsiv_COMPILER_APPLECLANG_VERSION ==  800  (Xcode 8.0)                 (LLVM 3.9.0)
// AppleClang  8.0.0  __apple_build_version__ ==  8000042  nsiv_COMPILER_APPLECLANG_VERSION ==  800  (Xcode 8.1, 8.2, 8.2.1)     (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020038  nsiv_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3)                 (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020041  nsiv_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3.1)               (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020042  nsiv_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3.2, 8.3.3)        (LLVM 3.9.0)
// AppleClang  9.0.0  __apple_build_version__ ==  9000037  nsiv_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.0)                 (LLVM 4.0.0?)
// AppleClang  9.0.0  __apple_build_version__ ==  9000038  nsiv_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.1)                 (LLVM 4.0.0?)
// AppleClang  9.0.0  __apple_build_version__ ==  9000039  nsiv_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.2)                 (LLVM 4.0.0?)
// AppleClang  9.1.0  __apple_build_version__ ==  9020039  nsiv_COMPILER_APPLECLANG_VERSION ==  910  (Xcode 9.3, 9.3.1)          (LLVM 5.0.2?)
// AppleClang  9.1.0  __apple_build_version__ ==  9020039  nsiv_COMPILER_APPLECLANG_VERSION ==  910  (Xcode 9.4, 9.4.1)          (LLVM 5.0.2?)
// AppleClang 10.0.0  __apple_build_version__ == 10001145  nsiv_COMPILER_APPLECLANG_VERSION == 1000  (Xcode 10.0, 10.1)          (LLVM 6.0.1?)
// AppleClang 10.0.1  __apple_build_version__ == 10010046  nsiv_COMPILER_APPLECLANG_VERSION == 1001  (Xcode 10.2, 10.2.1, 10.3)  (LLVM 7.0.0?)
// AppleClang 11.0.0  __apple_build_version__ == 11000033  nsiv_COMPILER_APPLECLANG_VERSION == 1100  (Xcode 11.1, 11.2, 11.3)    (LLVM 8.0.0?)

#define nsiv_COMPILER_VERSION( major, minor, patch )  ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined( __apple_build_version__ )
# define nsiv_COMPILER_APPLECLANG_VERSION nsiv_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
# define nsiv_COMPILER_CLANG_VERSION 0
#elif defined( __clang__ )
# define nsiv_COMPILER_APPLECLANG_VERSION 0
# define nsiv_COMPILER_CLANG_VERSION nsiv_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define nsiv_COMPILER_APPLECLANG_VERSION 0
# define nsiv_COMPILER_CLANG_VERSION 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define nsiv_COMPILER_GNUC_VERSION  nsiv_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
# define nsiv_COMPILER_GNUC_VERSION  0
#endif

// Presence of language and library features:

#define nsiv_HAVE( feature )  ( nsiv_HAVE_##feature )

#ifdef _HAS_CPP0X
# define nsiv_HAS_CPP0X  _HAS_CPP0X
#else
# define nsiv_HAS_CPP0X  0
#endif

#define nsiv_CPP11_90   (nsiv_CPP11_OR_GREATER || nsiv_COMPILER_MSVC_VER >= 1500)
#define nsiv_CPP11_100  (nsiv_CPP11_OR_GREATER || nsiv_COMPILER_MSVC_VER >= 1600)
#define nsiv_CPP11_110  (nsiv_CPP11_OR_GREATER || nsiv_COMPILER_MSVC_VER >= 1700)
#define nsiv_CPP11_120  (nsiv_CPP11_OR_GREATER || nsiv_COMPILER_MSVC_VER >= 1800)
#define nsiv_CPP11_140  (nsiv_CPP11_OR_GREATER || nsiv_COMPILER_MSVC_VER >= 1900)

#define nsiv_CPP14_000  (nsiv_CPP14_OR_GREATER)

#define nsiv_CPP17_000  (nsiv_CPP17_OR_GREATER)
#define nsiv_CPP17_140  (nsiv_CPP17_OR_GREATER || nsiv_COMPILER_MSVC_VER >= 1900)

#define nsiv_CPP20_000  (nsiv_CPP20_OR_GREATER)

// Presence of C++11 language features:

#define nsiv_HAVE_CONSTEXPR_11           nsiv_CPP11_140
#define nsiv_HAVE_IS_DEFAULT             nsiv_CPP11_120
#define nsiv_HAVE_IS_DELETE              nsiv_CPP11_120
#define nsiv_HAVE_NOEXCEPT               nsiv_CPP11_140
#define nsiv_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  nsiv_CPP11_120
#define nsiv_HAVE_STATIC_ASSERT          nsiv_CPP11_90
#define nsiv_HAVE_TRAILING_RETURN_TYPE   nsiv_CPP11_120
#define nsiv_HAVE_VALUE_INITIALIZATION   nsiv_CPP11_120

// Presence of C++14 language features:

#define nsiv_HAVE_CONSTEXPR_14           nsiv_CPP14_000

// Presence of C++17 language features:

#define nsiv_HAVE_DEDUCTION_GUIDES       nsiv_CPP17_000
#define nsiv_HAVE_NODISCARD              nsiv_CPP17_000

// Presence of C++20 language features:

#define nsiv_HAVE_CONSTEXPR_20           nsiv_CPP20_000

// Presence of C++11 library features:

#define nsiv_HAVE_IS_TRIVIAL             nsiv_CPP11_110
#define nsiv_HAVE_IS_TRIVIALLY_COPYABLE  nsiv_CPP11_110 && !nsiv_BETWEEN(nsiv_COMPILER_GNUC_VERSION, 1, 500) // GCC >= 5
#define nsiv_HAVE_IS_CONSTRUCTIBLE       nsiv_CPP11_110
#define nsiv_HAVE_IS_COPY_CONSTRUCTIBLE  nsiv_CPP11_110
#define nsiv_HAVE_IS_MOVE_CONSTRUCTIBLE  nsiv_CPP11_110
#define nsiv_HAVE_IS_NOTHROW_CONSTRUCTIBLE nsiv_CPP11_110
#define nsiv_HAVE_IS_NOTHROW_COPY_CONSTRUCTIBLE nsiv_CPP11_110
#define nsiv_HAVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE nsiv_CPP11_110
#define nsiv_HAVE_IS_COPY_ASSIGNABLE     nsiv_CPP11_110
#define nsiv_HAVE_IS_NOTHROW_ASSIGNABLE  nsiv_CPP11_110
#define nsiv_HAVE_IS_NOTHROW_MOVE_ASSIGNABLE  nsiv_CPP11_110

#define nsiv_HAVE_REFERENCE_WRAPPER      nsiv_CPP11_110

#define nsiv_HAVE_REMOVE_CV              nsiv_CPP11_90
#define nsiv_HAVE_REMOVE_REFERENCE       nsiv_CPP11_90

#define nsiv_HAVE_TYPE_TRAITS            nsiv_CPP11_110
#define nsiv_HAVE_TR1_TYPE_TRAITS        ((!! nsiv_COMPILER_GNUC_VERSION ) && nsiv_CPP11_OR_GREATER)

#define nsiv_HAVE_DECAY                  nsiv_CPP11_110
#define nsiv_HAVE_DECAY_TR1              nsiv_HAVE_TR1_TYPE_TRAITS

#define nsiv_HAVE_IS_SAME                nsiv_HAVE_TYPE_TRAITS
#define nsiv_HAVE_IS_SAME_TR1            nsiv_HAVE_TR1_TYPE_TRAITS

// Presence of C++14 library features:

// Presence of C++17 library features:

#define nsiv_HAVE_UNCAUGHT_EXCEPTIONS    nsiv_CPP17_140

// Presence of C++ language features:

#if nsiv_HAVE_CONSTEXPR_11
# define nsiv_constexpr constexpr
#else
# define nsiv_constexpr /*constexpr*/
#endif

#if nsiv_HAVE_CONSTEXPR_14
# define nsiv_constexpr14 constexpr
#else
# define nsiv_constexpr14 /*constexpr*/
#endif

#if nsiv_HAVE_CONSTEXPR_20
# define nsiv_constexpr20 constexpr
#else
# define nsiv_constexpr20 /*constexpr*/
#endif

// #if !nsiv_CONFIG_NO_CONSTEXPR
// #define nsiv_constexpr_ext  constexpr
// #else
// # define nsiv_constexpr_ext /*constexpr*/
// #endif

#if nsiv_HAVE( IS_DELETE )
# define nsiv_is_delete = delete
# define nsiv_is_delete_access public
#else
# define nsiv_is_delete
# define nsiv_is_delete_access private
#endif

#if nsiv_HAVE_NOEXCEPT
# define nsiv_noexcept noexcept
# define nsiv_noexcept_op(expr) noexcept(expr)
#else
# define nsiv_noexcept /*noexcept*/
# define nsiv_noexcept_op(expr) /*noexcept(expr)*/
#endif

#if nsiv_HAVE_NODISCARD
# define nsiv_nodiscard [[nodiscard]]
#else
# define nsiv_nodiscard /*[[nodiscard]]*/
#endif

#if nsiv_HAVE_STATIC_ASSERT
# define nsiv_static_assert(expr, msg) static_assert((expr), msg)
#else
# define nsiv_static_assert(expr, msg) /*static_assert((expr), msg)*/
#endif

// Additional includes:

#include <memory>
#include <utility>

#if nsiv_HAVE_TYPE_TRAITS
# include <type_traits>
#elif nsiv_HAVE_TR1_TYPE_TRAITS
# include <tr1/type_traits>
#endif

// Method enabling (return type):

#if nsiv_HAVE( TYPE_TRAITS )
# define nsiv_ENABLE_IF_R_(VA, R)  typename std::enable_if< (VA), R >::type
#else
# define nsiv_ENABLE_IF_R_(VA, R)  R
#endif

// Method enabling (function template argument):

#if nsiv_HAVE( TYPE_TRAITS ) && nsiv_HAVE( DEFAULT_FUNCTION_TEMPLATE_ARG )
// VS 2013 seems to have trouble with SFINAE for default non-type arguments:
# if !nsiv_BETWEEN( nsiv_COMPILER_MSVC_VERSION, 1, 140 )
#  define nsiv_ENABLE_IF_(VA) , typename std::enable_if< ( VA ), int >::type = 0
# else
#  define nsiv_ENABLE_IF_(VA) , typename = typename std::enable_if< ( VA ), ::nonstd::scope::enabler >::type
# endif
#else
# define  nsiv_ENABLE_IF_(VA)
#endif

// Namespace nonstd:

namespace nonstd { namespace iv {

namespace std11 {

    using std::default_delete;
    using std::allocator_arg_t;
}

namespace std14 {
}

namespace std17 {

    // using std::in_place_t;
}

// 4.1. Additions in [memory.syn] 20.2.2:

// [indirect.value], class template indirect_value

template< typename T > struct default_copy;
template< typename T > struct copier_traits;

template
<
    typename T
    , typename C = default_copy<T>
    , typename D = typename copier_traits<C>::deleter_type
>
class indirect_value;

template< typename T, typename ...Ts >
constexpr indirect_value<T> make_indirect_value( Ts &&... ts );

template< typename T, typename A = std::allocator<T>, typename... Ts >
constexpr indirect_value<T> allocate_indirect_value( std11::allocator_arg_t, A & a, Ts &&... ts );

template< typename T >
constexpr void swap( indirect_value<T> & p, indirect_value<T> & u ) noexcept;

// 4.2. X.X Class template copier_traits [copier.traits]

template< typename T >
struct copier_traits
{
    using deleter_type = typename T::deleter_type; // *see below*;
};

// Type: T::deleter_type if the qualified-id T::deleter_type is valid and denotes a type;
// otherwise, void (*)(U*) if T is of the form U* (*)(V) for types U and V;
// otherwise, there is no member deleter_type.

// 4.3. X.Y Class template default_copy [default.copy]

template< typename T >
struct default_copy
{
    using deleter_type = std11::default_delete<T>;
    constexpr T* operator()(T const & t) const { return new T(t); }
};

// 4.4. X.Z Class template indirect_value [indirect_value]

// 4.4.1. X.Z.1 Class template indirect_value general [indirect_value.general]

// 4.4.2. X.Z.2 Class template indirect_value synopsis [indirect_value.synopsis]

template
<
    typename T
    , typename C // = default_copy<T>
    , typename D // = typename copier_traits<C>::deleter_type
>
class indirect_value
{
public:
    using value_type = T;

    // Constructors:

    nsiv_constexpr indirect_value() noexcept {}
    nsiv_constexpr explicit indirect_value( T * p, C c = C{}, D d = D{} );

    nsiv_constexpr indirect_value( indirect_value const & p );
    nsiv_constexpr indirect_value( indirect_value && p) noexcept;

    template< typename ...Ts >
    nsiv_constexpr indirect_value( nonstd_lite_in_place_t(T), Ts &&... ts );  // See below

    // Destructor:

    nsiv_constexpr20 ~indirect_value() {}

    // Assignment:

    nsiv_constexpr indirect_value & operator=( indirect_value const & p);
    nsiv_constexpr indirect_value & operator=( indirect_value && p ) noexcept;

    // Modifiers:

    nsiv_constexpr void swap( indirect_value<T> & p ) noexcept;

    // Observers:

    nsiv_constexpr14 T & operator*();
    nsiv_constexpr14 T * operator->();
    nsiv_constexpr T const & operator*() const;
    nsiv_constexpr const T * operator->() const;
    nsiv_constexpr explicit operator bool() const noexcept;
};

// indirect_value creation:

template< typename T, typename ...Ts >
nsiv_constexpr indirect_value<T> make_indirect_value( Ts &&... ts);  // See below

template< typename T, typename A /*= std::allocator<T>*/, typename... Ts >
nsiv_constexpr indirect_value<T> allocate_indirect_value( std11::allocator_arg_t, A & a, Ts &&... ts );

// indirect_value specialized algorithms:

template< typename T >
nsiv_constexpr void swap(indirect_value<T>& p, indirect_value<T>& u) noexcept;

}} // end namespace nonstd::iv

// Provide in namespace nonstd:

namespace nonstd {

    using nonstd::iv::default_copy;
    using nonstd::iv::copier_traits;

    using nonstd::iv::indirect_value;

    using nonstd::iv::make_indirect_value;
    using nonstd::iv::allocate_indirect_value;

    using nonstd::iv::swap;
} // namespace nonstd

#endif // nsiv_USES_STD_INDIRECT_VALUE

#endif // NONSTD_INDIRECT_VALUE_LITE_HPP
