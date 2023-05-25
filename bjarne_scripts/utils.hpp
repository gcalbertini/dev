#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept> // for error
#include <iostream>  //for std namespace stuff

#ifndef UTILS_HPP
#define UTILS_HPP

void error(const std::string &message)
{
    throw std::runtime_error(message);
}

bool isDouble(const std::string &str)
{
    std::istringstream iss(str);
    double value;
    iss >> value;
    return !iss.fail() && iss.eof(); // no error occurs and end of stream reached
}

#endif
