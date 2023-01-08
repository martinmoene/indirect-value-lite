// include/nonstd/indirect_value.hpp
// p1950, http://wg21.link/p1950

#include <memory>
#include <utility>

#define nsiv_constexpr   constexpr
#define nsiv_constexpr14 constexpr
#define nsiv_constexpr20 constexpr

namespace nonstd { namespace iv {

namespace std11 {

    using std::default_delete;
    using std::allocator_arg_t;
}

namespace std14 {
}

namespace std17 {

    using std::in_place_t;
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

    constexpr indirect_value() noexcept {};
    constexpr explicit indirect_value( T * p, C c = C{}, D d = D{} );

    constexpr indirect_value( indirect_value const & p );
    constexpr indirect_value( indirect_value && p) noexcept;

    template< typename ...Ts >
    constexpr indirect_value( std17::in_place_t, Ts &&... ts );  // See below

    // Destructor:

    constexpr ~indirect_value() {}

    // Assignment:

    constexpr indirect_value & operator=( indirect_value const & p);
    constexpr indirect_value & operator=( indirect_value && p ) noexcept;

    // Modifiers:

    constexpr void swap( indirect_value<T> & p ) noexcept;

    // Observers:

    constexpr T & operator*();
    constexpr T * operator->();
    constexpr T const & operator*() const;
    constexpr const T * operator->() const;
    constexpr explicit operator bool() const noexcept;
};

// indirect_value creation:

template< typename T, typename ...Ts >
constexpr indirect_value<T> make_indirect_value( Ts &&... ts);  // See below

template< typename T, typename A /*= std::allocator<T>*/, typename... Ts >
constexpr indirect_value<T> allocate_indirect_value( std11::allocator_arg_t, A & a, Ts &&... ts );

// indirect_value specialized algorithms:

template< typename T >
constexpr void swap(indirect_value<T>& p, indirect_value<T>& u) noexcept;

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
