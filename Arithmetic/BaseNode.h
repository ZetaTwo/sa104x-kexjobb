#pragma once

#include <stdint.h>
#include <istream>

#include "types.h"

/**  The basic node from which all nodes in a Byte Tree inherit.
  */
class BaseNode
{
public:
	enum NodeType { 
		NODE = 0, /**< A node which contains other nodes. */
		INT_LEAF = 1, /**< An IntLeaf which contains a number. */
		DATA_LEAF = 2 /**< A DataLeaf which contains a string or vector of bytes. */
	};

	/** The BaseNode contructor.
	 *  \param[in] type What kind of node this is.
	 */
	BaseNode(BaseNode::NodeType type);
	~BaseNode(void);

	/** Returns what type the node is
	 *  \return The Node's type.
	 */
	BaseNode::NodeType getType(void) const;

	/** Returns how long the node is.
	 *  For a Node this returns the number of children.
	 *  For an IntLeaf this returns the number of bytes the number needs.
	 *  \return The length of the node.
	 */
	virtual int32_t getLength(void) const = 0;

	/** Returns the node's data.
	 *  Returns the node's data as a byte vector without the 5 byte prefix.
	 *  \return The node's data without header.
	 */
	virtual bytevector toVector(void) const = 0;
	
	/** Returns the node's data with header.
	 *  Returns the node's data as a byte vector with the 5 byte prefix.
	 *  \return The node's data with header.
	 */
	bytevector serialize() const;

    /** Returns the node's data with header as a string.
	 *  Returns the node's data as a string with the 5 byte prefix.
	 *  \return The node's data with header.
	 */
	std::string serializeString(void) const;    

	/** Returns the concatenation of two nodes data.
	 *  Returns the node's data with header concatenated with the data of the other node.
	 *  \param[in] other The node to concatenate to the node.
	 *  \return The two nodes data concatenated.
	 */
	bytevector concatData(const BaseNode * const other) const;


private:
	/** Indicates what type of node this is.
	 */
	const BaseNode::NodeType type;

protected:
	/** Copies a node.
	 *  Creates a copy of the provided node and returns a pointer to the copy.
	 *  \param[in] node A pointer to the node we want to copy.
	 *  \return A pointer to the copy of node.
	 */
	static BaseNode *copy(const BaseNode *node);

	/** Reads the header for a node.
	 *  Reads the first 5 bytes from file and extracts the type and length of the node into type and length.
	 *  \param[in] file The stream from where we want to read type and length.
	 *  \param[out] type The type of node
	 *  \param[out] length The length of the node
	 */
	static void ReadNodeHeader(std::istream &file, char &type, uint32_t &length);
};