// Header file

#include "nonstd/indirect_value.hpp"

class widget
{
public:
    widget();

    widget( widget && rhs ) noexcept;
    widget( widget const & rhs );

    widget & operator=( widget && rhs ) noexcept;
    widget & operator=( const widget & rhs );

    ~widget();

    int fortytwo() const;

private:
    class impl;
    nonstd::indirect_value< impl > pimpl;
};
