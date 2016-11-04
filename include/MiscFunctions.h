#ifndef MISCFUNCTIONS_H_INCLUDED
#define MISCFUNCTIONS_H_INCLUDED

#include <sstream>
#include <string>

using namespace std;

template <typename T>
string to_string(T val)
{
    stringstream stream;
    stream << val;
    return stream.str();
}


#endif // MISCFUNCTIONS_H_INCLUDED
