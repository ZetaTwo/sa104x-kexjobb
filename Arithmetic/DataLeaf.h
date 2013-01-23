#pragma once
#include "baseleaf.h"

#include <vector>

class DataLeaf :
	public BaseLeaf
{
public:
	DataLeaf(void);
	explicit DataLeaf(int32_t size);
	~DataLeaf(void);

	std::vector<char> &getData(void);
	const std::vector<char> &getData(void) const;
	virtual std::vector<char> toVector(void) const;
	virtual int32_t getLength(void) const;

	DataLeaf &operator=(const DataLeaf &leaf);

private:
	std::vector<char> data;
};

