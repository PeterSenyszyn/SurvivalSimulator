#ifndef STRINGHELPERS_H
#define STRINGHELPERS_H

#include <sstream>

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

#endif // STRINGHELPERS_H
