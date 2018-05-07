#ifndef _OFFWIREMESSAGE_HG_
#define _OFFWIREMESSAGE_HG_

#include "VisionMessage.h"
#include <string>

/**
 *
 */
class OffWireMessage : public VisionMessage
{
public:
	OffWireMessage(std::string message);
	virtual ~OffWireMessage();

	bool IsValid(void);
	std::string GetType(void);
	std::string GetMessage(void);

private:
	bool mValid = false;
	std::string mType = "unknown";
	std::string mMessage = "{}";
};

#endif
