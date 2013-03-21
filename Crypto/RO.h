#pragma once

#include "Node.h"

#include <string>
#include <vector>

class RO
{
public:
	RO(bytevector (*hash)(bytevector data), int Nout);
	~RO(void);

	IntLeaf operator()(bytevector data);
private:
	bytevector (*hash)(bytevector data);
	IntLeaf Nout;
};

