#include "VisionServer.h"
#include <sys/socket.h>
#include <sys/types.h>

VisionServer* VisionServer::pInstance = 0;

/**
 *
 */
VisionServer::VisionServer()
{
	this->bIsRunning = true;
	this->pTimer = new Timer();
}

/**
 *
 */
VisionServer::VisionServer(int port)
{
	this->pAdbBridge = new AdbBridge();
	this->iPort = port;

    this->pAdbBridge->Start();
    this->pAdbBridge->ReversePortForward(iPort, iPort);

    vThreads.push_back(std::thread(&AppMaintenanceThread, pInstance, "Maintenance Thread"));
}

/**
 *
 */
VisionServer::~VisionServer()
{
	delete this->pAdbBridge;
	for (auto& t : vThreads)
	{
	    t.join();
	}
}

/**
 *
 */
VisionServer* VisionServer::GetInstance()
{
    if (VisionServer::pInstance == 0)
    {
    	VisionServer::pInstance = new VisionServer(8254);
    }

    return VisionServer::pInstance;
}

/**
 *
 */
void VisionServer::Run()
{
	while (this->bIsRunning)
	{

	}
}

/**
 *
 */
void VisionServer::AppMaintenanceThread()
{
	while (true)
	{
		if (pTimer->GetFPGATimestamp() - dLastMessageReceivedTime > .1)
		{
			pAdbBridge->ReversePortForward(iPort, iPort);
			bIsConnected = false;
		}
		else
		{
			bIsConnected = true;
		}

		if (bWantsAppRestart)
		{
			pAdbBridge->RestartApp();
			bWantsAppRestart = false;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
