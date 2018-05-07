#ifndef _VISION_VISIONSERVER_HG_
#define _VISION_VISIONSERVER_HG_

#include "AdbBridge.h"
#include "SocketServer.h"
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
	void AppMaintenanceThread(void);

	static VisionServer* pInstance;

	Timer* pTimer;
	AdbBridge* pAdbBridge;
	SocketServer* pSocketServer;

	bool bIsRunning;
	bool bWantsAppRestart = false;
	bool bIsConnected = false;
	std::vector<std::thread> vThreads;
	int iPort;
};

#endif
