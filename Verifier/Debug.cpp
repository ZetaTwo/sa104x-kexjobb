#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>

#include "Debug.h"

void print_debug(string name, long long value)
{
    #ifdef DEBUG
    std::cout << name << ": " << std::endl << value << std::endl << std::endl;
    #endif

}

void print_debug(string name, string value)
{
    #ifdef DEBUG
    std::cout << name << ": " << std::endl << value << std::endl << std::endl;
    #endif
}

void print_debug(string name, bytevector data)
{
    #ifdef DEBUG
    std::cout << name << ": " << std::endl;
    std::ostringstream ss;
    ss << std::hex << std::uppercase << std::setfill( '0' );
    for(bytevector::iterator itr = data.begin(); itr < data.end(); itr++)
    {
	ss << std::setw( 2 ) << (int)*itr;
    }
    std::cout << ss.str() << std::endl << std::endl;
    #endif
}

void print_debug(string name, int index, bytevector data)
{
    char namestr[100];
    sprintf(namestr, (name + "_%d").c_str(), index);
    print_debug(namestr, data);
}

void print_debug(string comment)
{
    #ifdef DEBUG
    std::cout << comment << std::endl << std::endl;
    #endif
}
