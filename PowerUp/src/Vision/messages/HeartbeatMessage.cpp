#include "HeartbeatMessage.h"
#include <string>

HeartbeatMessage* HeartbeatMessage::pInstance = 0;

/**
 *
 */
HeartbeatMessage::HeartbeatMessage()
{
}

/**
 *
 */
HeartbeatMessage::~HeartbeatMessage()
{
}

/**
 *
 */
HeartbeatMessage* HeartbeatMessage::GetInstance()
{
    if (HeartbeatMessage::pInstance == 0)
    {
    	HeartbeatMessage::pInstance = new HeartbeatMessage();
    }

    return HeartbeatMessage::pInstance;
}

/**
 *
 */
std::string HeartbeatMessage::GetType()
{
	return "heartbeat";
}

/**
 *
 */
std::string HeartbeatMessage::GetMessage()
{
	return "{}";
}

