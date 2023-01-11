// Implementation file

#include "03-pimpl.hpp"
#include <iostream>

class widget::impl
{
public:
    int fortytwo() const { return 42; }
};

// Special-member functions need to be defined in a the same TU as <code data-opaque
// bs-autolink-syntax='`widget::impl`'>widget::impl</code>.
widget::widget()
    : pimpl( new impl )
{}

widget::widget( widget && rhs ) noexcept             = default;
widget::widget( widget const & rhs )                 = default;

widget & widget::operator=( widget && rhs ) noexcept = default;
widget & widget::operator=( const widget & rhs )     = default;

widget::~widget()                                    = default;

int widget::fortytwo() const
{
    return pimpl->fortytwo();
}

int main()
{
    widget w;
    return w.fortytwo();
}

// cl -nologo -EHsc -I../include 03-pimpl.cpp & 03-pimpl.exe
// echo %ERRORLEVEL%
