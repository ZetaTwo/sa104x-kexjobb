#pragma once
#include "baseleaf.h"

#include <vector>
#include <istream>
#include <string>

/** A node which contains a string or vector of bytes.
 */
class DataLeaf :
	public BaseLeaf
{
public:

	/** The default constructor.
	 *  Creates an empty DataLeaf.
	 */
	DataLeaf(void);

	/** Creates a DataLeaf of a set size.
	 *  Creates a DataLeaf which has a preset capacity of size.
	 *  \param[in] size The size of the DataLeaf
	 */
	explicit DataLeaf(int32_t size);

	/** Creates a DataLeaf from a stream.
	 *  Creates a DataLeaf from the data in the stream.
	 *  \param[in] file The stream which contains the data of the DataLeaf.
	 */
	DataLeaf(std::istream &file);
	
	/** Creates a DataLeaf from a filename.
	 *  Creates a DataLeaf from the data in the file at path str.
	 *  \param[in] str The path to the file which contains the data of the DataLeaf.
	 */
	DataLeaf(std::string str);
	~DataLeaf(void);

	/** Get the contents of DataLeaf.
	 *  Returns a reference to the data contained in the DataLeaf.
	 *  \return A reference to the byte vector containing the DataLeaf data.
	 */
	bytevector &getData(void);

	/** Get the contents of DataLeaf.
	 *  Returns the data contained in the DataLeaf.
	 *  \return A byte vector containing the DataLeaf data.
	 */
	const bytevector &getData(void) const;
	
	virtual bytevector toVector(void) const;
	
	virtual int32_t getLength(void) const;

	DataLeaf &operator=(const DataLeaf &leaf);

private:
	bytevector data;
};

