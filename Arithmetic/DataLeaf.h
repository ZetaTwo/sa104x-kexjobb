#pragma once
#include "baseleaf.h"

#include <vector>
#include <istream>
#include <string>

class DataLeaf :
	public BaseLeaf
{
public:
	DataLeaf(void);
	explicit DataLeaf(int32_t size);
	DataLeaf(std::istream &file);
	DataLeaf(std::string str);
	~DataLeaf(void);

	std::vector<unsigned char> &getData(void);
	const std::vector<unsigned char> &getData(void) const;
	virtual std::vector<unsigned char> toVector(void) const;
	virtual int32_t getLength(void) const;

	DataLeaf &operator=(const DataLeaf &leaf);

private:
	std::vector<unsigned char> data;
};

