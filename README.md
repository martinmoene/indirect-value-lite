# indirect-value-lite
indirect_value lite – An indirect value-type for ~~C++98,~~ C++11 and later in a single-file header-only library  (p1950)

[![Language](https://img.shields.io/badge/C%2B%2B-11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://github.com/martinmoene/indirect-value-lite/actions/workflows/ci.yml/badge.svg)](https://github.com/martinmoene/indirect-value-lite/actions/workflows/ci.yml) <!--[![Build status](https://ci.appveyor.com/api/projects/status/1ha3wnxtam547m8p?svg=true)](https://ci.appveyor.com/project/martinmoene/indirect-value-lite) -->[![Version](https://badge.fury.io/gh/martinmoene%2Findirect-value-lite.svg)](https://github.com/martinmoene/indirect-value-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://github.com/martinmoene/indirect-value-lite/blob/master/include/nonstd/indirect_value.hpp) <!--[![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/indirect-value-lite) [![Try it on wandbox](https://img.shields.io/badge/on-wandbox-blue.svg)]() -->[![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/s9j8njMM9)

## References

W. Brown. [n3339](http://wg21.link/n3339): A Preliminary Proposal for a Deep-Copying Smart Pointer, Walter E. Brown, 2012.  
J. Coe. [p0201](http://wg21.link/p0201): polymorphic_value: A Polymorphic Value Type for C++.  
J. Coe. [p1950](http://wg21.link/p1950): indirect_value: A Free-Store-Allocated Value Type For C++.  
J. Coplien. Advanced C++ Programming Styles and Idioms (Addison-Wesley), James O. Coplien. 1992.  
C. Ericson. [Memory Optimization, Christer Ericson, Games Developers Conference](http://realtimecollisiondetection.net/pubs/GDC03_Ericson_Memory_Optimization.ppt) (PPT). 2003.  
R. Grimm. [Visiting a std::variant with the Overload Pattern](https://www.modernescpp.com/index.php/visiting-a-std-variant-with-the-overload-pattern). 2021.  
H. Hinnant. “[Incomplete types and shared_ptr / unique_ptr](http://howardhinnant.github.io/incomplete.html)”. 2011.  
M. Knejp. [p0316](http://wg21.link/p0316): allocate_unique and allocator_delete.  
H. Sutter. "[Pimpls - Beauty Marks You Can Depend On](http://www.gotw.ca/publications/mill04.htm)", Herb Sutter. 1998.  
J.B.Coe. Reference implementation: [indirect_value](https://github.com/jbcoe/indirect_value).  
S. Meyers. Effective Modern C++, Item 22: When using the Pimpl Idiom, define special member functions in the implementation file, Scott Meyers. 2014.  
A. Upadyshev. [PIMPL, Rule of Zero and Scott Meyers, Andrey Upadyshev](http://oliora.github.io/2015/12/29/pimpl-and-rule-of-zero.html). 2015.  
