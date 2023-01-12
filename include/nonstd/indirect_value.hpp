//
// Copyright (c) 2023-2023 Martin Moene
//
// https://github.com/martinmoene/indirect-value-lite (p1950)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// Portions Copyright (c) 2019 The Indirect Value Authors. All Rights Reserved.
//
// https://github.com/jbcoe/indirect_value
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

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

#if !defined( nsiv_CONFIG_NO_EXTENSION_REF_QUALIFIED_OPERATORS )
# define nsiv_CONFIG_NO_EXTENSION_REF_QUALIFIED_OPERATORS  ( nsiv_CONFIG_NO_EXTENSIONS )
#endif

#if !defined( nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS )
# define nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS  ( nsiv_CONFIG_NO_EXTENSIONS )
#endif

#if !defined( nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS )
# define nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS  ( nsiv_CONFIG_NO_EXTENSIONS )
#endif

#if !defined( nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS )
# define nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS  ( nsiv_CONFIG_NO_EXTENSIONS )
#endif

#if !defined( nsiv_CONFIG_NO_EXTENSION_STD_HASH )
# define nsiv_CONFIG_NO_EXTENSION_STD_HASH  ( nsiv_CONFIG_NO_EXTENSIONS )
#endif

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

// If std::indirect_value is available, it's in <memory>, included further below.

#define nsiv_HAVE_STD_INDIRECT_VALUE  0

#define nsiv_USES_STD_INDIRECT_VALUE  ( (nsiv_CONFIG_SELECT_INDIRECT_VALUE == nsiv_INDIRECT_VALUE_STD) || ((nsiv_CONFIG_SELECT_INDIRECT_VALUE == nsiv_INDIRECT_VALUE_DEFAULT) && nsiv_HAVE_STD_INDIRECT_VALUE) )

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
// std::indirect_value is non-existent (yet)
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

// MSVC warning suppression macros:

#if nsiv_COMPILER_MSVC_VERSION >= 140 && ! nsiv_COMPILER_NVCC_VERSION
# define nsiv_SUPPRESS_MSGSL_WARNING(expr)        [[gsl::suppress(expr)]]
# define nsiv_SUPPRESS_MSVC_WARNING(code, descr)  __pragma(warning(suppress: code) )
# define nsiv_DISABLE_MSVC_WARNINGS(codes)        __pragma(warning(push))  __pragma(warning(disable: codes))
# define nsiv_RESTORE_MSVC_WARNINGS()             __pragma(warning(pop ))
#else
# define nsiv_SUPPRESS_MSGSL_WARNING(expr)
# define nsiv_SUPPRESS_MSVC_WARNING(code, descr)
# define nsiv_DISABLE_MSVC_WARNINGS(codes)
# define nsiv_RESTORE_MSVC_WARNINGS()
#endif

// Suppress the following MSVC GSL warnings:
// - C4814: in C++14 'constexpr' will not imply 'const'; consider explicitly specifying 'const'

nsiv_DISABLE_MSVC_WARNINGS( 4814 )

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
#define nsiv_HAVE_INLINE_VARIABLE        nsiv_CPP17_000

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

#define nsiv_HAVE_IS_FINAL               nsiv_CPP14_000

// Presence of C++17 library features:

#define nsiv_HAVE_IS_NOTHROW_SWAPPABLE   nsiv_CPP17_000
#define nsiv_HAVE_UNCAUGHT_EXCEPTIONS    nsiv_CPP17_140
#define nsiv_HAVE_VOID_T                 nsiv_CPP17_000

// Presence of C++ language features:

#if nsiv_HAVE_CONSTEXPR_11
# define nsiv_constexpr constexpr
# define nsiv_mutable11 mutable
#else
# define nsiv_constexpr /*constexpr*/
# define nsiv_mutable11 /*mutable*/
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

#if defined( __cpp_lib_three_way_comparison ) && defined( __cpp_lib_concepts )
#include <compare>
#endif

// Method enabling (requires clause):

#ifdef __cpp_concepts
# define nsiv_REQUIRES(x) requires x
#else
# define nsiv_REQUIRES(x) /*requires x*/
#endif

// Namespace nonstd::iv

namespace nonstd { namespace iv {

// C++11 polyfills:

namespace std11 {

    using std::default_delete;
    using std::allocator_arg_t;

    using std::is_empty;
} // namespace std11

// C++14 polyfills:

namespace std14 {

#if nsiv_HAVE_IS_FINAL
    using std::is_final;
#else
    // implementation requires compiler support.
    template< typename T > struct is_final : std::false_type{};
#endif

#if nsiv_CPP11_100
#if nsiv_HAVE( DEFAULT_FUNCTION_TEMPLATE_ARG )
template< typename T, typename U = T >
#else
template< typename T, typename U /*= T*/ >
#endif
nsiv_constexpr14 T exchange( T & obj, U && new_value )
{
    T old_value = std::move( obj );
    obj = std::forward<U>( new_value );
    return old_value;
}
#endif

} // namespace std14

// C++17 polyfills:

namespace std17 {

// std::in_place_t, see nonstd_lite_in_place_t() above.

#if nsiv_HAVE_IS_NOTHROW_SWAPPABLE
    using std::is_swappable;
    using std::is_nothrow_swappable;
#else

#if nsiv_HAVE_VOID_T
    using ::std::void_t;
#else
    template< typename... Ts >
    struct make_void { typedef void type; };

    template< typename... Ts >
    using void_t = typename make_void<Ts...>::type;
#endif

namespace detail {

using std::swap;

struct is_swappable
{
    template< typename T, typename = decltype( swap( std::declval<T&>(), std::declval<T&>() ) ) >
    static std::true_type test( int /* unused */);

    template< typename >
    static std::false_type test(...);
};

struct is_nothrow_swappable
{
    // wrap noexcept(expr) in separate function as work-around for VC140 (VS2015):

    template< typename T >
    static nsiv_constexpr bool satisfies()
    {
        return noexcept( swap( std::declval<T&>(), std::declval<T&>() ) );
    }

    template< typename T >
    static auto test( int ) -> std::integral_constant<bool, satisfies<T>()>{}

    template< typename >
    static auto test(...) -> std::false_type;
};
} // namespace detail

// is [nothrow] swappable:

template< typename T >
struct is_swappable : decltype( detail::is_swappable::test<T>(0) ){};

template< typename T >
struct is_nothrow_swappable : decltype( detail::is_nothrow_swappable::test<T>(0) ){};

#endif // nsiv_HAVE_IS_NOTHROW_SWAPPABLE

} // namespace std17

// is_complete_v, used with nsiv_REQUIRES():

#ifdef __cpp_concepts
    template< typename T, typename = void > constexpr bool is_complete_v = false;
    template< typename T                  > constexpr bool is_complete_v< T, std::enable_if_t< sizeof(T) >> = true;
#endif

// 4.1. Additions in [memory.syn] 20.2.2:

// 4.?. X.X Class bad_indirect_value_access [...] - Extension

#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    class bad_indirect_value_access : public std::exception
    {
    public:
        const char * what() const noexcept override { return "bad indirect_value access"; }
    };
#endif

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
    nsiv_constexpr T * operator()( T const & t ) const { return new T(t); }
};

// 4.4. X.Z Class template indirect_value [indirect_value]
// 4.4.1. X.Z.1 Class template indirect_value general [indirect_value.general]
// 4.4.2. X.Z.2 Class template indirect_value synopsis [indirect_value.synopsis]

// MSVC requires __declspec(empty_bases) to apply empty base class optimisation (EBCO) for more than one base class:
// - https://en.cppreference.com/w/cpp/language/ebo
// - https://learn.microsoft.com/en-us/cpp/cpp/empty-bases?view=msvc-170
#if     nsiv_COMPILER_MSVC_VERSION >= 140 || ( defined(_MSVC_LANG) && _MSVC_LANG >= 201402 )
#define nsiv_EMPTY_BASES_DECORATION  __declspec( empty_bases )
#else
#define nsiv_EMPTY_BASES_DECORATION
#endif

// Provide for empty base class for copier:

template
<
    typename C
    , bool CanBeEmptyBaseClass = std11::is_empty<C>::value && !std14::is_final<C>::value
>
class indirect_value_copy_base
{
protected:
    nsiv_constexpr indirect_value_copy_base() = default;

    nsiv_constexpr indirect_value_copy_base( C const & copier )
        : m_copier( copier ) {}
    nsiv_constexpr indirect_value_copy_base( C && copier )
        : m_copier( std::move( copier ) ) {}

    nsiv_constexpr14 C &       get()       nsiv_noexcept { return m_copier; }
    nsiv_constexpr   C const & get() const nsiv_noexcept { return m_copier; }

    C m_copier;
};

template< typename C >
class indirect_value_copy_base< C, true > : private C
{
protected:
    nsiv_constexpr indirect_value_copy_base() = default;

    nsiv_constexpr indirect_value_copy_base( C const & copier )
        : C( copier ) {}
    nsiv_constexpr indirect_value_copy_base( C && copier )
        : C( std::move( copier ) ) {}

    nsiv_constexpr14 C &       get()       nsiv_noexcept { return *this; }
    nsiv_constexpr   C const & get() const nsiv_noexcept { return *this; }
};

// Provide for empty base class for deleter:

template
<
    typename D
    , bool CanBeEmptyBaseClass = std11::is_empty<D>::value && !std14::is_final<D>::value
>
class indirect_value_delete_base
{
protected:
    nsiv_constexpr indirect_value_delete_base() = default;

    nsiv_constexpr indirect_value_delete_base( D const & deleter )
        : m_deleter( deleter ) {}
    nsiv_constexpr indirect_value_delete_base( D && deleter )
        : m_deleter( std::move( deleter ) ) {}

    nsiv_constexpr14 D &       get()       nsiv_noexcept { return m_deleter; }
    nsiv_constexpr   D const & get() const nsiv_noexcept { return m_deleter; }

    D m_deleter;
};

template< typename D >
class indirect_value_delete_base< D, true > : private D
{
protected:
    nsiv_constexpr indirect_value_delete_base() = default;

    nsiv_constexpr indirect_value_delete_base( const D & deleter )
        : D( deleter) {}
    nsiv_constexpr indirect_value_delete_base( D && deleter )
        : D( std::move( deleter ) ) {}

    nsiv_constexpr14 D &       get()       nsiv_noexcept { return *this; }
    nsiv_constexpr   D const & get() const nsiv_noexcept { return *this; }
};

// Class indirect_value:

template
<
    typename T
    , typename C = default_copy<T>
    , typename D = typename copier_traits<C>::deleter_type
>
class nsiv_EMPTY_BASES_DECORATION indirect_value
    : private indirect_value_copy_base< C >
    , private indirect_value_delete_base< D >
{
    using copy_base   = indirect_value_copy_base< C >;
    using delete_base = indirect_value_delete_base< D >;

public:
    using value_type = T;

    // Constructors:

    nsiv_constexpr indirect_value() nsiv_noexcept = default;

    // Effects       : Constructs a indirect_value which owns p, initializing the stored pointer with p.
    //                 The copier and deleter of the indirect_value constructed are moved from c and d.
    //                 If p is null, creates an empty object.
    // Constraints   : is_nothrow_move_assignable_v<C> is true.
    //                 is_nothrow_move_assignable_v<D> is true.
    // Preconditions : C and D meet the Cpp17CopyConstructible requirements.
    //                 If the arguments c and/or d are not supplied, then C and/or D respectively are default constructible types that are not pointer types.
    //                 If p is non-null then the expression c(*p) returns a non-null T* is as if copy constructed from *p.
    //                 The expression d(p) has well-defined behaviour, and does not throw exceptions.
    // Postconditions: bool(*this) == bool(p).
    // Mandates      : The expression d(p) is well-formed.

    nsiv_constexpr explicit indirect_value( T * p, C c = C{}, D d = D{} ) nsiv_noexcept
        : copy_base(   std::move( c ) )
        , delete_base( std::move( d ) )
        , m_ptr( p )
    {}

    // Effects       : Move-constructs an indirect_value instance from p.
    //                 If p has a custom copier and deleter then the copier and deleter
    //                 of the indirect_value constructed are the same as those in p.
    // Postconditions: *this contains the old value of p.
    //                 p is empty.

    nsiv_constexpr indirect_value( indirect_value const & other )
        nsiv_REQUIRES( (!is_complete_v<T>) || std::is_copy_constructible_v<T> )
        : copy_base(   other.get_c() )
        , delete_base( other.get_d() )
        , m_ptr( other.make_raw_copy() )
    {}

    // Effects       : Move-constructs an indirect_value instance from p.
    //                 If p has a custom copier and deleter then the copier and deleter of
    //                 the indirect_value constructed are the same as those in p.
    // Postconditions: *this contains the old value of p.
    //                 p is empty.

    nsiv_constexpr indirect_value( indirect_value && other ) nsiv_noexcept
        : copy_base(   std::move( other.get_c() ) )
        , delete_base( std::move( other.get_d() ) )
        , m_ptr( std14::exchange( other.m_ptr, nullptr ) )
    {}

    // Effects      : Constructs an indirect_value which owns an object of type T
    //                direct-non-list-initialized with std::forward<Ts>(ts)...
    // Throws       : Any exception thrown by the selected constructor of T or
    //                bad_alloc if required storage cannot be obtained.
    // Preconditions: is_same_v<C, default_copy> && is_same_v<D, default_delete>.

    template< typename ...Ts >
    nsiv_constexpr indirect_value( nonstd_lite_in_place_t(T), Ts &&... ts )
          : m_ptr( new T( std::forward<Ts>(ts)...) )
    {}

    // Destructor:

    // Effects: If *this there are no effects.
    //          If a custom deleter d is present then d(p) is called and the copier and deleter are destroyed.
    //          Otherwise the destructor of the managed object is called.
    // Remarks: The constructor must work with pointer to an complete type T.

    nsiv_constexpr20 ~indirect_value() { reset(); }

    // Assignment:

    // Constraints   : is_copy_assignable_v<C> is true. is_copy_assignable_v<D> is true.
    // Effects       : If p is empty, assigns an empty object. Otherwise creates an object that owns a copy of the object managed by p. The copy is created by the copier in p, and the copier and deleter of *this are copied from those in p.
    // Remarks       : The function must work with pointer to an complete type T.
    // Throws        : Any exception thrown by the copier or bad_alloc if required storage cannot be obtained.
    // Returns       : *this.
    // Postconditions: bool(*this) == bool(p).

    nsiv_constexpr14 indirect_value & operator=( indirect_value const & other )
        nsiv_REQUIRES( (!is_complete_v<T>) || std::is_copy_constructible_v<T> )
    {
        auto scoped_copy = other.make_scoped_copy();

        reset();
        copy_base::operator=(   other );
        delete_base::operator=( other );
        m_ptr = scoped_copy.release();

        return *this;
    }

    // Constraints   : is_nothrow_move_assignable_v<C> is true.
    //                 is_nothrow_move_assignable_v<D> is true.
    // Effects       : Ownership of the resource managed by p is transferred to this.
    //                 If p has a custom copier and deleter then the copier and deleter of *this is the same as those in p.
    // Remarks       : The function must work with pointer to an complete type T.
    // Returns       : *this.
    // Postconditions: *this contains the old value of p.
    //                 p is empty.

    nsiv_constexpr14 indirect_value & operator=( indirect_value && other ) nsiv_noexcept
    {
        if ( this != &other )
        {
            reset();
            copy_base::operator=  ( std::move( other ) );
            delete_base::operator=( std::move( other ) );
            m_ptr = std14::exchange( other.m_ptr, nullptr );
        }

        return *this;
    }

    // Modifiers:

    nsiv_constexpr14 void swap( indirect_value & other )
        nsiv_noexcept_op( std17::is_nothrow_swappable<C>::value && std17::is_nothrow_swappable<D>::value )
    {
        using std::swap;
        swap( get_c(), other.get_c() );
        swap( get_d(), other.get_d() );
        swap(   m_ptr, other.m_ptr   );
    }

    // Observers:

    // Configurable extension (w.r.t. p1950r2): reference qualified operators:

#if !nsiv_CONFIG_NO_EXTENSION_REF_QUALIFIED_OPERATORS
    nsiv_constexpr14 T &        operator*()       &  nsiv_noexcept { return *m_ptr; }
    nsiv_constexpr   T const &  operator*() const &  nsiv_noexcept { return *m_ptr; }

    nsiv_constexpr14 T &&       operator*()       && nsiv_noexcept { return std::move( *m_ptr ); }
    nsiv_constexpr   T const && operator*() const && nsiv_noexcept { return std::move( *m_ptr ); }
#else
    nsiv_constexpr14 T &        operator*()       nsiv_noexcept { return *m_ptr; }
    nsiv_constexpr   T const &  operator*() const nsiv_noexcept { return *m_ptr; }
#endif

    nsiv_constexpr14 T *        operator->()       nsiv_noexcept { return m_ptr; }
    nsiv_constexpr   T const *  operator->() const nsiv_noexcept { return m_ptr; }

    nsiv_constexpr explicit operator bool() const nsiv_noexcept { return m_ptr != nullptr; }

    // Configurable extension (w.r.t. p1950r2): has_value() and value():

#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS

    nsiv_constexpr bool has_value() const nsiv_noexcept { return m_ptr != nullptr; }

    nsiv_constexpr14 T & value() &
    {
        if ( !m_ptr )
            throw bad_indirect_value_access();
        return *m_ptr;
    }

    nsiv_constexpr14 T const & value() const &
    {
        if ( !m_ptr )
            throw bad_indirect_value_access();
        return *m_ptr;
    }

    nsiv_constexpr14 T && value() &&
    {
        if ( !m_ptr )
            throw bad_indirect_value_access();
        return std::move( *m_ptr );
    }

    nsiv_constexpr14 T const && value() const &&
    {
        if ( !m_ptr )
            throw bad_indirect_value_access();
        return std::move( *m_ptr );
    }
#endif  // nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS

    // Configurable extension (w.r.t. p1950r2): get_copier() and get_deleter():

#if !nsiv_CONFIG_NO_EXTENSION_GET_CPY_DEL_MEMBERS
    using copier_type  = C;
    using deleter_type = D;
    nsiv_constexpr14 copier_type  &       get_copier()        nsiv_noexcept { return get_c(); }
    nsiv_constexpr   copier_type  const & get_copier()  const nsiv_noexcept { return get_c(); }
    nsiv_constexpr14 deleter_type &       get_deleter()       nsiv_noexcept { return get_d(); }
    nsiv_constexpr   deleter_type const & get_deleter() const nsiv_noexcept { return get_d(); }
#endif

private:
    nsiv_constexpr14 C &       get_c()       nsiv_noexcept { return copy_base::get(); }
    nsiv_constexpr   C const & get_c() const nsiv_noexcept { return copy_base::get(); }
    nsiv_constexpr14 D &       get_d()       nsiv_noexcept { return delete_base::get(); }
    nsiv_constexpr   D const & get_d() const nsiv_noexcept { return delete_base::get(); }

    nsiv_constexpr14 void reset() nsiv_noexcept
    {
        if ( m_ptr )
        {
            // Avoid m_ptr to be deleted more than once:
            get_d()( std14::exchange( m_ptr, nullptr ) );
        }
    }

    nsiv_constexpr T * make_raw_copy() const
    {
        return m_ptr ? get_c()( *m_ptr ) : nullptr;
    }

    nsiv_constexpr auto make_scoped_copy() const -> std::unique_ptr<T, std::reference_wrapper<const D>>
    {
        return { make_raw_copy(), std::ref( get_d() ) };
    }

    nsiv_mutable11 T * m_ptr = nullptr;
};

// Support for object allocation and deallocation:

namespace detail {

template < typename T, typename A, typename... Args >
nsiv_constexpr20 T * allocate_object( A & a, Args &&... args )
{
    using t_allocator = typename std::allocator_traits< A >::template rebind_alloc< T >;
    using t_traits    = std::allocator_traits< t_allocator >;

    t_allocator t_alloc( a );
    T * mem = t_traits::allocate( t_alloc, 1 );

    try
    {
        t_traits::construct( t_alloc, mem, std::forward< Args >( args )... );
        return mem;
    }
    catch (...)
    {
        t_traits::deallocate( t_alloc, mem, 1 );
        throw;
    }
}

template < typename T, typename A >
nsiv_constexpr14 void deallocate_object( A & a, T * p )
{
    using t_allocator = typename std::allocator_traits< A >::template rebind_alloc< T >;
    using t_traits    = std::allocator_traits< t_allocator >;

    t_allocator t_alloc( a );
    t_traits::destroy( t_alloc, p );
    t_traits::deallocate( t_alloc, p, 1 );
};

template < typename T, typename A >
struct allocator_delete : A
{
    nsiv_constexpr allocator_delete( A & a )
        : A( a )
    {}

    nsiv_constexpr14 void operator()( T * ptr ) const nsiv_noexcept
    {
        static_assert( 0 < sizeof( T ), "can't delete an incomplete type" );
        detail::deallocate_object( *this, ptr );
    }
};

template < typename T, typename A >
struct allocator_copy : A
{
    using deleter_type = allocator_delete< T, A >;

    nsiv_constexpr allocator_copy( A & a )
        : A( a )
    {}

    nsiv_constexpr T * operator()( const T & t ) const
    {
        return detail::allocate_object< T >( *this, t );
    }
};

} // namespace detail

// indirect_value creation:

// Constraints  : is_constructible_v<U, Ts...> is true.
// Preconditions: U meets the Cpp17CopyConstructible requirements.
// Returns      : A indirect_value<T> owning an object of type direct-non-list-initialized with std::forward<Ts>(ts)....
// Preconditions: is_same_v<C, default_copy> && is_same_v<D, default_delete>.

template< typename T, typename ...Ts >
nsiv_constexpr indirect_value<T> make_indirect_value( Ts &&... ts)
{
    return indirect_value<T>( nonstd_lite_in_place(T), std::forward<Ts>(ts)... );
}

// Constraints  : is_constructible_v<U, Ts...> is true.
// Preconditions: U meets the Cpp17CopyConstructible requirements.
// Returns      : A indirect_value<T,C,D> owning an object of type direct-non-list-initialized with std::forward<Ts>(ts)....
// Preconditions: is_same_v<C, allocator_copy> && is_same_v<D, allocator_delete>.

template< typename T, typename A = std::allocator<T>, typename... Ts >
nsiv_constexpr20 auto allocate_indirect_value( std11::allocator_arg_t, A & a, Ts &&... ts )
    -> indirect_value<T, detail::allocator_copy<T, A>, detail::allocator_delete<T, A>>
{
    auto * ptr = detail::allocate_object<T>(a, std::forward<Ts>(ts)...);

    try
    {
        return indirect_value<T, detail::allocator_copy<T, A>, detail::allocator_delete<T, A>>( ptr, {a}, {a} );
    }
    catch (...)
    {
        detail::deallocate_object( a, ptr );
        throw;
    }
}

// indirect_value specialized algorithms:

template< typename T, typename C, typename D >
nsiv_constexpr14 typename std::enable_if< std17::is_swappable<C>::value && std17::is_swappable<D>::value >::type
swap( indirect_value<T,C,D> & lhs, indirect_value<T,C,D> & rhs )
    nsiv_noexcept_op( nsiv_noexcept_op( lhs.swap(rhs) ) )
{
    lhs.swap( rhs );
}

// Configurable extension (w.r.t. p1950r2): relational operators.

#if !nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS

// Comparison between two indirect_values:

template< typename T1, typename C1, typename D1, typename T2, typename C2, typename D2 >
constexpr bool operator==( indirect_value< T1, C1, D1 > const & lhs,  indirect_value< T2, C2, D2 > const & rhs )
{
    return bool( lhs ) == bool( rhs ) && ( !bool( lhs ) || *lhs == *rhs );
}

template< typename T1, typename C1, typename D1, typename T2, typename C2, typename D2 >
constexpr bool operator!=( indirect_value< T1, C1, D1 > const & lhs,  indirect_value< T2, C2, D2 > const & rhs )
{
    return bool( lhs ) != bool( rhs ) || ( bool( lhs ) && *lhs != *rhs );
}

template< typename T1, typename C1, typename D1, typename T2, typename C2, typename D2 >
constexpr bool operator<( indirect_value< T1, C1, D1 > const & lhs,  indirect_value< T2, C2, D2 > const & rhs )
{
    return bool( rhs ) && ( !bool( lhs ) || *lhs < *rhs );
}

template< typename T1, typename C1, typename D1, typename T2, typename C2, typename D2 >
constexpr bool operator>( indirect_value< T1, C1, D1 > const & lhs,  indirect_value< T2, C2, D2 > const & rhs )
{
    return bool( lhs ) && ( !bool( rhs ) || *lhs > *rhs );
}

template< typename T1, typename C1, typename D1, typename T2, typename C2, typename D2 >
constexpr bool operator<=( indirect_value< T1, C1, D1 > const & lhs,  indirect_value< T2, C2, D2 > const & rhs )
{
    return !bool( lhs ) || ( bool( rhs ) && *lhs <= *rhs );
}

template< typename T1, typename C1, typename D1, typename T2, typename C2, typename D2 >
constexpr bool operator>=( indirect_value< T1, C1, D1 > const & lhs,  indirect_value< T2, C2, D2 > const & rhs )
{
    return !bool( rhs ) || ( bool( lhs ) && *lhs >= *rhs );
}

#if defined( __cpp_lib_three_way_comparison ) && defined( __cpp_lib_concepts )

template< typename T1, typename C1, typename D1, std::three_way_comparable_with< T1 > T2, typename C2, typename D2 >
constexpr std::compare_three_way_result_t< T1, T2 >
operator<=>( indirect_value< T1, C1, D1 > const & lhs,  indirect_value< T2, C2, D2 > const & rhs )
{
    if ( lhs && rhs )
    {
        return *lhs <=> *rhs;
    }
    return bool( lhs ) <=> bool( rhs );
}
#endif // 3-way comparison && concepts

// Comparisons with nullptr_t:

template< typename T, typename C, typename D >
constexpr bool operator==( indirect_value< T, C, D > const & lhs, std::nullptr_t ) noexcept
{
    return !lhs;
}

template< typename T, typename C, typename D >
constexpr bool operator==( std::nullptr_t, indirect_value< T, C, D > const & rhs ) noexcept
{
    return !rhs;
}

template< typename T, typename C, typename D >
constexpr bool operator!=( indirect_value< T, C, D > const & lhs, std::nullptr_t ) noexcept
{
    return bool( lhs );
}

template< typename T, typename C, typename D >
constexpr bool operator!=( std::nullptr_t, indirect_value< T, C, D > const & rhs ) noexcept
{
    return bool( rhs );
}

template< typename T, typename C, typename D >
constexpr bool operator<( indirect_value< T, C, D > const &, std::nullptr_t ) noexcept
{
    return false;
}

template< typename T, typename C, typename D >
constexpr bool operator<( std::nullptr_t, indirect_value< T, C, D > const & rhs ) noexcept
{
    return bool( rhs );
}

template< typename T, typename C, typename D >
constexpr bool operator>( indirect_value< T, C, D > const & lhs, std::nullptr_t ) noexcept
{
    return bool( lhs );
}

template< typename T, typename C, typename D >
constexpr bool operator>( std::nullptr_t, indirect_value< T, C, D > const & ) noexcept
{
    return false;
}

template< typename T, typename C, typename D >
constexpr bool operator<=( indirect_value< T, C, D > const & lhs, std::nullptr_t ) noexcept
{
    return !lhs;
}

template< typename T, typename C, typename D >
constexpr bool operator<=( std::nullptr_t, indirect_value< T, C, D > const & ) noexcept
{
    return true;
}

template< typename T, typename C, typename D >
constexpr bool operator>=( indirect_value< T, C, D > const &, std::nullptr_t ) noexcept
{
    return true;
}

template< typename T, typename C, typename D >
constexpr bool operator>=( std::nullptr_t, indirect_value< T, C, D > const & rhs ) noexcept
{
    return !rhs;
}

#if defined( __cpp_lib_three_way_comparison ) && defined( __cpp_lib_concepts )

template< typename T, typename C, typename D >
constexpr std::strong_ordering operator<=>( indirect_value< T, C, D > const & lhs, std::nullptr_t )
{
    return bool( lhs ) <=> false;
}

#endif // 3-way comparison && concepts

// Comparison with T:

template< typename T >
struct _enable_if_convertible_to_bool : std::enable_if< std::is_convertible< T, bool >::value, bool >{};

template< typename LHS, typename RHS >
struct _enable_if_comparable_with_equal
    : _enable_if_convertible_to_bool< decltype( std::declval< const LHS & >() == std::declval< const RHS & >() ) >{};

template< typename LHS, typename RHS >
struct _enable_if_comparable_with_not_equal
    : _enable_if_convertible_to_bool< decltype( std::declval< const LHS & >() != std::declval< const RHS & >() ) >{};

template< typename LHS, typename RHS >
struct _enable_if_comparable_with_less
    : _enable_if_convertible_to_bool< decltype( std::declval< const LHS & >() < std::declval< const RHS & >() ) >{};

template< typename LHS, typename RHS >
struct _enable_if_comparable_with_greater
    : _enable_if_convertible_to_bool< decltype( std::declval< const LHS & >() > std::declval< const RHS & >() ) >{};

template< typename LHS, typename RHS >
struct _enable_if_comparable_with_less_equal
    : _enable_if_convertible_to_bool< decltype( std::declval< const LHS & >() <= std::declval< const RHS & >() ) >{};

template< typename LHS, typename RHS >
struct _enable_if_comparable_with_greater_equal
    : _enable_if_convertible_to_bool< decltype( std::declval< const LHS & >() >= std::declval< const RHS & >() ) >{};

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<U>::value, int >::type = 0 >
constexpr auto operator==( indirect_value< T, C, D > const & lhs, U const & rhs )
    -> typename _enable_if_comparable_with_equal< T, U >::type
        // nsiv_REQUIRES( (!std::is_null_pointer_v<U>) )
{
    return lhs && *lhs == rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<T>::value, int >::type = 0 >
constexpr auto operator==( T const & lhs, indirect_value< U, C, D > const & rhs )
    -> typename _enable_if_comparable_with_equal< T, U >::type
        // nsiv_REQUIRES( (!std::is_null_pointer_v<T>) )
{
    return rhs && lhs == *rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<U>::value, int >::type = 0 >
constexpr auto operator!=( indirect_value< T, C, D > const & lhs, U const & rhs )
    -> typename _enable_if_comparable_with_not_equal< T, U >::type
{
    return !lhs || *lhs != rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<T>::value, int >::type = 0 >
constexpr auto operator!=( T const & lhs, indirect_value< U, C, D > const & rhs )
    -> typename _enable_if_comparable_with_not_equal< T, U >::type
{
    return !rhs || lhs != *rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<U>::value, int >::type = 0 >
constexpr auto operator<( indirect_value< T, C, D > const & lhs, U const & rhs )
    -> typename _enable_if_comparable_with_less< T, U >::type
{
    return !lhs || *lhs < rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<T>::value, int >::type = 0 >
constexpr auto operator<( T const & lhs, indirect_value< U, C, D > const & rhs )
    -> typename _enable_if_comparable_with_less< T, U >::type
{
    return rhs && lhs < *rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<U>::value, int >::type = 0 >
constexpr auto operator>( indirect_value< T, C, D > const & lhs, U const & rhs )
    -> typename _enable_if_comparable_with_greater< T, U >::type
{
    return lhs && *lhs > rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<T>::value, int >::type = 0 >
constexpr auto operator>( T const & lhs, indirect_value< U, C, D > const & rhs )
    -> typename _enable_if_comparable_with_greater< T, U >::type
{
    return !rhs || lhs > *rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<U>::value, int >::type = 0 >
constexpr auto operator<=( indirect_value< T, C, D > const & lhs, U const & rhs )
    -> typename _enable_if_comparable_with_less_equal< T, U >::type
{
    return !lhs || *lhs <= rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<T>::value, int >::type = 0 >
constexpr auto operator<=( T const & lhs, indirect_value< U, C, D > const & rhs )
    -> typename _enable_if_comparable_with_less_equal< T, U >::type
{
    return rhs && lhs <= *rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<U>::value, int >::type = 0 >
constexpr auto operator>=( indirect_value< T, C, D > const & lhs, U const & rhs )
    -> typename _enable_if_comparable_with_greater_equal< T, U >::type
{
    return lhs && *lhs >= rhs;
}

template< typename T, typename C, typename D, typename U, typename std::enable_if< !std::is_null_pointer<T>::value, int >::type = 0 >
constexpr auto operator>=( T const & lhs, indirect_value< U, C, D > const & rhs )
    -> typename _enable_if_comparable_with_greater_equal< T, U >::type
{
    return !rhs || lhs >= *rhs;
}

#if defined( __cpp_lib_three_way_comparison ) && defined( __cpp_lib_concepts )

template< typename >
inline constexpr bool _is_indirect_value_v = false;

template< typename T, typename C, typename D >
inline constexpr bool _is_indirect_value_v< indirect_value< T, C, D > > = true;

template< typename T, typename C, typename D, typename U >
    requires( !_is_indirect_value_v< U > ) && std::three_way_comparable_with< T, U >
std::compare_three_way_result_t< T, U > operator<=>( indirect_value< T, C, D > const & lhs, U const & rhs )
{
    return bool( lhs ) ? *lhs <=> rhs : std::strong_ordering::less;
}
#endif  // 3-way comparison && concepts

#endif // nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS

}} // end namespace nonstd::iv

// Configurable extension (w.r.t. p1950r2): struct hash in std namespace.

#if !nsiv_CONFIG_NO_EXTENSION_STD_HASH

namespace nonstd { namespace iv {

template< typename IndirectValue, bool Enabled >
struct _conditionally_enabled_hash
{
    using VTHash = std::hash< typename IndirectValue::value_type >;

    nsiv_constexpr std::size_t operator()( const IndirectValue & key ) const
        noexcept( noexcept( VTHash{}( *key ) ) )
    {
        return key ? VTHash{}( *key ) : 0;
    }
};

template < typename T >
struct _conditionally_enabled_hash< T, false >
{
    // conditionally disabled hash base
    nsiv_constexpr _conditionally_enabled_hash() = delete;
    nsiv_constexpr _conditionally_enabled_hash( const _conditionally_enabled_hash & ) = delete;
    nsiv_constexpr _conditionally_enabled_hash & operator=( const _conditionally_enabled_hash & ) = delete;
};

}} // end namespace nonstd::iv

// Provide in namespace std:

namespace std {
template< typename T, typename C, typename D >
struct hash< ::nonstd::iv::indirect_value<T, C, D> >
    : ::nonstd::iv::_conditionally_enabled_hash<
        ::nonstd::iv::indirect_value<T, C, D>
        , std::is_default_constructible<hash<T> >::value
    >{};
} // namespace std

#endif // nsiv_CONFIG_NO_EXTENSION_STD_HASH

// Provide in namespace nonstd:

namespace nonstd {

    using nonstd::iv::default_copy;
    using nonstd::iv::copier_traits;

    using nonstd::iv::indirect_value;

    using nonstd::iv::make_indirect_value;
    using nonstd::iv::allocate_indirect_value;

    using nonstd::iv::swap;

#if !nsiv_CONFIG_NO_EXTENSION_VALUE_MEMBERS
    using nonstd::iv::bad_indirect_value_access;
#endif

#if !nsiv_CONFIG_NO_EXTENSION_RELATIONAL_OPERATORS
    using nonstd::iv::operator==;
    using nonstd::iv::operator!=;
    using nonstd::iv::operator<;
    using nonstd::iv::operator<=;
    using nonstd::iv::operator>;
    using nonstd::iv::operator>=;
# if defined( __cpp_lib_three_way_comparison ) && defined( __cpp_lib_concepts )
    using nonstd::iv::operator<=>;
# endif
#endif
} // namespace nonstd

nsiv_RESTORE_MSVC_WARNINGS()

#endif // nsiv_USES_STD_INDIRECT_VALUE

#endif // NONSTD_INDIRECT_VALUE_LITE_HPP
