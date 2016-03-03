#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <string>

class CommandLineBullshit
{
public:
    CommandLineBullshit(const std::string arg) : m_arg(arg) {}

private:
    std::string m_arg;
};

#endif
