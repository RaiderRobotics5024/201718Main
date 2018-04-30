#ifndef _VISION_VISIONSERVER_HG_
#define _VISION_VISIONSERVER_HG_

#include "AdbBridge.h"
#include <thread>
#include <vector>

/**
 *
 */
class VisionServer
{
public:
	virtual ~VisionServer();
	static VisionServer* GetInstance(void);
	void Run(void);

private:
	VisionServer();
	VisionServer(int port);
	static VisionServer* pInstance;

	AdbBridge* pAdbBridge;
	bool bIsRunning;
	std::vector<std::thread> vThreads;
};

#endif
