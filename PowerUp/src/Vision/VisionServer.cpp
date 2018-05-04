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
