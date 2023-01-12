# indirect-value-lite

indirect_value lite – An indirect value-type for C++11 and later in a single-file header-only library (p1950)

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://github.com/martinmoene/indirect-value-lite/actions/workflows/ci.yml/badge.svg)](https://github.com/martinmoene/indirect-value-lite/actions/workflows/ci.yml) <!--[![Build status](https://ci.appveyor.com/api/projects/status/1ha3wnxtam547m8p?svg=true)](https://ci.appveyor.com/project/martinmoene/indirect-value-lite) -->[![Version](https://badge.fury.io/gh/martinmoene%2Findirect-value-lite.svg)](https://github.com/martinmoene/indirect-value-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/indirect-value-lite/blob/master/include/nonstd/indirect_value.hpp) <!--[![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/indirect-value-lite) [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)]() -->[![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/s9j8njMM9)

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Other implementations of indirect_value](#other-implementations-of-indirect_value)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

<!-- - [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests) -->

## Example usage

```Cpp
#include "nonstd/indirect_value.hpp"
#include <iostream>

int main(int argc, char **)
{
}
```

TODO: write example.

### Compile and run

```Text
$ g++ -std=c++11 -Wall -I../include/ -o main.exe main.cpp && main.exe
```

## In a nutshell

**indirect_value lite** is a single-file header-only library to provide `indirect_value` type proposed for [C++23](http://wg21.link/p1950) for use with C++11 and later. If and when available, the standard library is used, unless [configured](#configuration) otherwise.

**Features and properties of indirect_value lite** are ease of installation (single header), freedom of dependencies other than the standard library. *indirect_value lite* shares the approach to in-place tags with any-lite, expected-lite, optional-lite and with variant-lite and these libraries can be used together.

**Limitations of indirect_value lite** are ... \[*to be summed up*\].

## License

*indirect_value lite* is distributed under the [Boost Software License](https://github.com/martinmoene/indirect-value-lite/blob/master/LICENSE.txt). It contains portions of the reference implementation by the *The Indirect Value Authors*, which has [MIT copyright](https://github.com/jbcoe/indirect_value/blob/main/LICENSE.txt).

## Dependencies

*indirect_value lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation

*indirect_value lite* is a single-file header-only library. Put `indirect_value.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

- [Documentation of `class indirect_value`](#documentation-of-class-indirect_value)
- [*indirect_value lite* implementation status](#indirect_value-lite-implementation-status)
- [Configuration](#configuration)

### Documentation of class indirect_value

\[*Envisioned*\] Depending on the compiler and C++ standard used, *indirect_value lite* behaves less or more like the standard's version. To get an idea of the capabilities of *indirect_value lite* with your configuration, look at the output of the [tests](test/indirect_value.t.cpp), issuing `indirect_value-main.t --pass @`.

There's no standard documentation available yet at cppreference for [`class indirect_value`](https://en.cppreference.com/w/cpp/???/indirect_value), which is proposed to be part of the [C++ dynamic memory management library](https://en.cppreference.com/w/cpp/memory).

#### Types and values in namespace nonstd

| Purpose               | Type / value                          | Notes                                           |
| --------------------- | ------------------------------------- | ----------------------------------------------- |
| Indirect value type   | class **indirect_value**              | &nbsp;                                          |
| Error reporting       | class **bad_indirect_value_access**   | (extension)                                     |
| Hash                  | class **std::hash**                   | specialisation (extension)                      |
| &nbsp;                | &nbsp;                                | &nbsp;                                          |
| In-place construction | struct **in_place_tag**               | &nbsp;                                          |
| &nbsp;                | **in_place**                          | select type or index for in-place construction  |
| &nbsp;                | **in_place_type**                     | select type for in-place construction           |
| &emsp;(variant)       | **in_place_index**                    | select index for in-place construction          |
| &nbsp;                | **in_place_t**                        | type or index for in-place construction         |
| &nbsp;                | **in_place_type_t**                   | type for in-place construction                  |
| &emsp;(variant)       | **in_place_index_t**                  | index for in-place construction                 |
| &nbsp;                | **nonstd_lite_in_place**( T)          | macro for alias template in_place               |
| &nbsp;                | **nonstd_lite_in_place_type**( T)     | macro for alias template in_place_type&lt;T>    |
| &emsp;(variant)       | **nonstd_lite_in_place_index**( T )   | macro for alias template in_place_index&lt;T>   |
| &nbsp;                | **nonstd_lite_in_place_t**( T)        | macro for alias template in_place_t             |
| &nbsp;                | **nonstd_lite_in_place_type_t**( T)   | macro for alias template in_place_type_t&lt;T>  |
| &emsp;(variant)       | **nonstd_lite_in_place_index_t**( T ) | macro for alias template in_place_index_t&lt;T> |

#### Interface of *indirect_value lite*

| Kind                 | Std    | Method                                                                                          | Result                       |
| -------------------- | ------ | ----------------------------------------------------------------------------------------------- | ---------------------------- |
| Types                | &nbsp; | **value_type**                                                                                  | T template type              |
| &nbsp;               | &nbsp; | **copier_type**                                                                                 | C template type (extension)  |
| &nbsp;               | &nbsp; | **deleter_type**                                                                                | D template type (extension)  |
| Construction         | &nbsp; | constexpr **indirect_value**() noexcept                                                         | default-construct            |
| &nbsp;               | &nbsp; | constexpr explicit **indirect_value**(T * p, C c=C{}, D d=D{})                                  | construct, own given pointer |
| &nbsp;               | &nbsp; | constexpr **indirect_value**(indirect_value const & other)                                      | copy-construct from other    |
| &nbsp;               | &nbsp; | constexpr **indirect_value**(indirect_value && other) noexcept                                  | move-construct from other    |
| &nbsp;               | &nbsp; | template&lt;class ...T><br>constexpr **indirect_value**(nonstd_lite_in_place_t(T), Ts &&... ts) | in-place construct           |
| &nbsp;               | &nbsp; | constexpr ~**indirect_value**()                                                                 | destroy current object       |
| Assignment<br>&nbsp; | &nbsp; | constexpr indirect_value &<br>**operator=**(indirect_value const & rhs)                         | copy-assign from other       |
| &nbsp;               | &nbsp; | constexpr indirect_value &<br>**operator=**(indirect_value && rhs) noexcept                     | move-assign from other       |
| Modifiers            | &nbsp; | constexpr void **swap**(indirect_value & other) noexcept(...)                                   | exchange objects             |
| Observers            | &nbsp; | constexpr T& **operator***() &                                                                  | owned object                 |
| &nbsp;               | &nbsp; | constexpr T const & **operator***() const &                                                     | owned object                 |
| &nbsp;               | &nbsp; | constexpr T && **operator***() && noexcept                                                      | owned object                 |
| &nbsp;               | &nbsp; | constexpr T const && **operator***() const && noexcept                                          | owned object                 |
| &nbsp;               | &nbsp; | constexpr T * **operator->**() noexcept                                                         | owned object                 |
| &nbsp;               | &nbsp; | constexpr T const * **operator->**() const noexcept                                             | owned object                 |
| &nbsp;               | &nbsp; | constexpr explicit **operator bool**() const noexcept                                           | engaged                      |
| &nbsp;               | &nbsp; | constexpr bool **has_value**() const noexcept                                                   | engaged (extension)          |
| &nbsp;               | &nbsp; | constexpr T & **value**() &                                                                     | may throw (extension)        |
| &nbsp;               | &nbsp; | constexpr T const & **value**() const &                                                         | may throw (extension)        |
| &nbsp;               | &nbsp; | constexpr T && **value**() &&                                                                   | may throw (extension)        |
| &nbsp;               | &nbsp; | constexpr T const && **value**() const &&                                                       | may throw (extension)        |
| &nbsp;               | &nbsp; | constexpr copier_type & **get_copier**() noexcept                                               | (extension)                  |
| &nbsp;               | &nbsp; | constexpr copier_type const & **get_copier**() const noexcept                                   | (extension)                  |
| &nbsp;               | &nbsp; | constexpr deleter_type & **get_deleter**() noexcept                                             | (extension)                  |
| &nbsp;               | &nbsp; | constexpr deleter_type const & **get_deleter**() const noexcept                                 | (extension)                  |

#### Algorithms for *indirect_value lite*

| Kind                           | Std    | Function                                                                                     | Result             |
| ------------------------------ | ------ | -------------------------------------------------------------------------------------------- | ------------------ |
| Create                         | &nbsp; | **make_indirect_value**()                                                                    | in-place construct |
| &nbsp;                         | &nbsp; | **allocate_indirect_value**()                                                                | in-place construct |
| Swap                           | &nbsp; | void **swap**(indirect_value & lhs, indirect_value & rhs)                                    | exchange contents  |
| Relational operators<br>&nbsp; | &nbsp; | template&lt;...> constexpr bool<br>operator**X**(indirect_value & lhs, indirect_value & rhs) | (extension)        |
| &nbsp;                         | &nbsp; | template&lt;...> constexpr bool<br>operator**X**(indirect_value & lhs, std::nullptr_t)       | (extension)        |
| &nbsp;                         | &nbsp; | template&lt;...> constexpr bool<br>operator**X**(std::nullptr_t, indirect_value & rhs)       | (extension)        |
| Three-way operators            | C++20  | template&lt;...> constexpr bool<br>operator**&lt;=>**(...)                                   | TODO (extension)   |

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *indirect_value lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/indirect_value.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define indirect_value_CPLUSPLUS 201103L`.

#### Select `std::indirect_value` or `nonstd::indirect_value`

The C++ standard does not yet provide type `std::indirect_value`.

<!-- At default, *indirect_value lite* uses `std::indirect_value` if it is available and lets you use it via namespace `nonstd`. You can however override this default and explicitly request to use `std::indirect_value` or indirect_value lite's `nonstd::indirect_value` as `nonstd::indirect_value` via the following macros.

-D<b>indirect_value\_CONFIG\_SELECT\_indirect_value</b>=indirect_value\_SELECT\_indirect_value\_NONSTD  
Define this to `indirect_value__CONFIG_SELECT_indirect_value_STD` to select `std::indirect_value` as `nonstd::indirect_value`. Define this to `indirect_value_SELECT_indirect_value_NONSTD` to select `nonstd::indirect_value` as `nonstd::indirect_value`. Default is undefined, which has the same effect as defining to `indirect_value_SELECT_indirect_value_NONSTD` currently (this may change to `indirect_value_SELECT_indirect_value_DEFAULT`). -->

#### Standard selection macro

\-D<b>indirect_value\_CPLUSPLUS</b>=201103L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

<!--#### Disable exceptions

-D<b>indirect_value_CONFIG_NO_EXCEPTIONS</b>=0
Define this to 1 if you want to compile without exceptions. If not defined, the header tries and detect if exceptions have been disabled (e.g. via `-fno-exceptions`). Default is undefined. -->

#### Disable extensions

-D<b>nsiv\_CONFIG\_NO\_EXTENSIONS</b>=0  
Define this to 1 if you want to compile without extensions with respect to [p1950r2 of October 2022](http://wg21.link/p1950r2). See below. Default is undefined, and all extensions are enabled.

#### Disable reference qualified operators extension

-D<b>nsiv\_CONFIG\_NO\_EXTENSION\_REF\_QUALIFIED\_OPERATORS</b>=0  
Define this to 1 if you want to compile without this extension. Default is undefined (extension enabled).

#### Disable `value()` members extension

-D<b>nsiv\_CONFIG\_NO\_EXTENSION\_VALUE\_MEMBERS</b>=0  
Define this to 1 if you want to compile without this extension. Default is undefined (extension enabled).

#### Disable `get_copier()`, `get_deleter()` extension

-D<b>nsiv\_CONFIG\_NO\_EXTENSION\_GET\_CPY\_DEL\_MEMBERS</b>=0  
Define this to 1 if you want to compile without this extension. Default is undefined (extension enabled).

#### Disable relational operators extension

-D<b>nsiv\_CONFIG\_NO\_EXTENSION\_RELATIONAL\_OPERATORS</b>=0  
Define this to 1 if you want to compile without this extension. Default is undefined (extension enabled).

#### Disable `std::hash` extension

-D<b>nsiv\_CONFIG\_NO\_EXTENSION\_STD\_HASH</b>=0  
Define this to 1 if you want to compile without this extension. Default is undefined (extension enabled).  
TODO: implement `std::hash`.

## Other implementations of indirect_value

J.B. Coe. Reference implementation: [indirect_value](https://github.com/jbcoe/indirect_value). An indirect value-type for C++. GitHub.  

## Notes and references

W. Brown. [n3339](http://wg21.link/n3339): A Preliminary Proposal for a Deep-Copying Smart Pointer, Walter E. Brown, 2012.  
J.B. Coe. [p0201](http://wg21.link/p0201): polymorphic_value: A Polymorphic Value Type for C++.  
J.B. Coe. [p1950](http://wg21.link/p1950): indirect_value: A Free-Store-Allocated Value Type For C++.  
J. Coplien. Advanced C++ Programming Styles and Idioms (Addison-Wesley), James O. Coplien. 1992.  
C. Ericson. [Memory Optimization, Christer Ericson, Games Developers Conference](http://realtimecollisiondetection.net/pubs/GDC03_Ericson_Memory_Optimization.ppt) (PPT). 2003.  
R. Grimm. [Visiting a std::variant with the Overload Pattern](https://www.modernescpp.com/index.php/visiting-a-std-variant-with-the-overload-pattern). 2021.  
H. Hinnant. “[Incomplete types and shared_ptr / unique_ptr](http://howardhinnant.github.io/incomplete.html)”. 2011.  
M. Knejp. [p0316](http://wg21.link/p0316): allocate_unique and allocator_delete.  
H. Sutter. "[Pimpls - Beauty Marks You Can Depend On](http://www.gotw.ca/publications/mill04.htm)", Herb Sutter. 1998.  
S. Meyers. Effective Modern C++, Item 22: When using the Pimpl Idiom, define special member functions in the implementation file, Scott Meyers. 2014.  
A. Upadyshev. [PIMPL, Rule of Zero and Scott Meyers, Andrey Upadyshev](http://oliora.github.io/2015/12/29/pimpl-and-rule-of-zero.html). 2015.  

## Appendix

<a id="a1"></a>
### A.1 Compile-time information

The version of *indirect_value lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

<a id="a2"></a>
### A.2 indirect_value lite test specification

<details>
<summary>click to expand</summary>
<p>

```Text
indirect_value: Allows to default construct (empty)
indirect_value: Allows to construct from pointer
indirect_value: Allows to in-place construct from arguments
indirect_value: Allows to copy-construct
indirect_value: Allows to move-construct
indirect_value: Allows to copy-assign
indirect_value: Allows to move-assign
indirect_value: Allows to swap (value)
indirect_value: Allows to swap (copier)
indirect_value: Allows to swap (deleter)
indirect_value: Allows to check if engaged, has_value() [extension]
indirect_value: Allows to obtain value (op->)
indirect_value: Allows to obtain value (op-> const)
indirect_value: Allows to obtain value (op* &)
indirect_value: Allows to obtain value (op* const &)
indirect_value: Allows to obtain value (op* &&)
indirect_value: Allows to obtain value (op* const &&)
indirect_value: Allows to obtain value (value() &) [extension]
indirect_value: Allows to obtain value (value() const &) [extension]
indirect_value: Allows to obtain value (value() &&) [extension]
indirect_value: Allows to obtain value (value() const &&) [extension]
indirect_value: No throw of exception on valid value access (value() &) [extension]
indirect_value: No throw of exception on valid value access(value() const &) [extension]
indirect_value: No throw of exception on valid value access(value() &&) [extension]
indirect_value: No throw of exception on valid value access(value() const &&) [extension]
indirect_value: Throws on bad value access (value() &) [extension]
indirect_value: Throws on bad value access (value() const &) [extension]
indirect_value: Throws on bad value access (value() &&) [extension]
indirect_value: Throws on bad value access (value() const &&) [extension]
indirect_value: Allows to obtain copier (get_copier() &) [extension]
indirect_value: Allows to obtain copier (get_copier() const &) [extension]
indirect_value: Allows to obtain deleter (get_deleter() &) [extension]
indirect_value: Allows to obtain deleter (get_deleter() const &) [extension]
indirect_value: Ensure using minimum space requirements
indirect_value: Ensure noexcept of observers
indirect_value: Ensure ref- and const-qualifier of observers
indirect_value: Ensure properties of bad_indirect_value_access [extension][TODO]
indirect_value: Ensure stats of copy and delete type [TODO]
indirect_value: Ensure protection against reentrancy [TODO]
indirect_value: Ensure protection against self-assign [TODO]
indirect_value: Ensure using source copier when copying [TODO]
indirect_value: Ensure working with an incomplete type [TODO]
make_indirect_value(): Allows to in-place construct an indirect value from parameters
allocate_indirect_value(): Allows to in-place construct an indirect value from parameters, with given allocator
swap(): Allows to swap
relational operators: Allows to compare indirect_value-s [extension]
relational operators: Allows to compare indirect_value with nullptr [extension]
relational operators: Allows to compare indirect_value with value convertible to its value_type [extension]
relational operators: Allows to 3-way compare indirect_value-s [extension]
relational operators: Allows to 3-way compare indirect_value with nullptr [extension]
relational operators: Allows to 3-way compare indirect_value with value convertible to its value_type [extension]
std::hash: Allows to hash an indirect_value [extension]
tweak header: reads tweak header if supported [tweak]
```

</p>
</details>
