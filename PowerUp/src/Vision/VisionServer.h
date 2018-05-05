#ifndef _VISION_VISIONSERVER_HG_
#define _VISION_VISIONSERVER_HG_

#include "AdbBridge.h"
#include <thread>
#include <chrono>
#include <vector>
#include <Timer.h>

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
	void AppMaintenanceThread(void);

	AdbBridge* pAdbBridge;
	Timer* pTimer;

	bool bIsRunning;
	bool bWantsAppRestart = false;
	bool bIsConnected = false;
	std::vector<std::thread> vThreads;
	int iPort;
	double dLastMessageReceivedTime = 0.0;
};

#endif
