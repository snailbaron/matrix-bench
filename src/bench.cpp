#include <map>
#include <string>
#include "bench.hpp"

static std::map<std::string, Method> methodByName = {
// OH MY GOD A MACRO
#define METHOD(NAME) { #NAME, NAME },

    METHOD(SIMPLE)

#undef METHOD
};

static std::map<Method, std::string> nameByMethod = {
// OH MY GOD ANOTHER ONE
#define METHOD(NAME) { NAME, #NAME },
    
    METHOD(SIMPLE)

#undef METHOD
};

std::istream & operator>>(std::istream &is, Method &m)
{
    std::string s;
    is >> s;

    if (methodByName.find(s) == methodByName.end()) {
        std::cerr << "MAKE ME FAIL SOMEHOW" << std::endl;
        return is;
    }

    m = methodByName[s];
    return is;
}

std::ostream & operator<<(std::ostream &os, const Method &m)
{
    os << nameByMethod[m];
    return os;
}