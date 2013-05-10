#ifndef VERIFIER_DEBUG
#define VERIFIER_DEBUG

#include <string>
#include "types.h"

using std::string;

void print_debug(string name, long long value);
void print_debug(string name, string value);
void print_debug(string name, bytevector data);
void print_debug(string comment);

#endif
