#pragma once
#include "basenode.h"

#include <vector>

/**  The basic leaf from which IntLeaf and DataLeaf inherit.
  */
class BaseLeaf :
	public BaseNode
{
public:
	/** The BaseLeaf contructor.
	 *  \param[in] type What kind of node this is.
	 */
	explicit BaseLeaf(BaseLeaf::NodeType type);
	~BaseLeaf(void);
};

