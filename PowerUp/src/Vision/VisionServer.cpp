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
    	VisionServer::pInstance = new VisionServer(5024);
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
