#ifndef _HEARTBEATMESSAGE_HG_
#define _HEARTBEATMESSAGE_HG_

#include "VisionMessage.h"

/**
 *
 */
class HeartbeatMessage : public VisionMessage
{
public:
	static HeartbeatMessage* GetInstance(void);
	std::string GetType(void);
	std::string GetMessage(void);

private:
	HeartbeatMessage();
	virtual ~HeartbeatMessage();

	static HeartbeatMessage* pInstance;
};

#endif
