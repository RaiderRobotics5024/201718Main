#ifndef _VISIONMESSAGE_HG_
#define _VISIONMESSAGE_HG_

#include <iostream>
#include <string>

/**
 *
 */
class VisionMessage
{
public:

    virtual std::string GetType() = 0;

    virtual std::string GetMessage() = 0;

    std::string ToJson(void)
    {
    	return std::string("{\"type\":\"") + GetType() + "\",\"message\":\"" + GetMessage() + "\"}";
    }
};

#endif
