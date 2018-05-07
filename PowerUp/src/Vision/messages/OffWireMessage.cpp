#include "OffWireMessage.h"
#include "../../include/json/json.hpp"

using json = nlohmann::json;

/**
 *
 */
OffWireMessage::OffWireMessage(std::string message)
{
	json j1 = json::parse(message);

	mType = j1["type"];
	mMessage = j1["message"];
	mValid = true;
}

/**
 *
 */
OffWireMessage::~OffWireMessage()
{
}

/**
 *
 */
bool OffWireMessage::IsValid()
{
	return mValid;
}

/**
 *
 */
std::string OffWireMessage::GetType()
{
	return mType;
}

/**
 *
 */
std::string OffWireMessage::GetMessage()
{
	return mMessage;
}
