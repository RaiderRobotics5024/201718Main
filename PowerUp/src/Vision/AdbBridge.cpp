#include "AdbBridge.h"
#include "../Utilities/Log.h"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>

/**
 *
 */
AdbBridge::AdbBridge()
{
}

/**
 *
 */
AdbBridge::~AdbBridge()
{
}

/**
 *
 */
bool AdbBridge::RunCommand(const char* cmd)
{
    char buffer[128];
    std::string result = "";

    FILE* pipe = popen(cmd, "r");
    if (!pipe) { LOG("[AdbBridge] popen failed"); return false; }

    try {
        while (!feof(pipe))
        {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...)
    {
        pclose(pipe);
        LOG("[AdbBridge] command - " << cmd << " - failed");
        return false;
    }
    pclose(pipe);

    return true;
}

/**
 *
 */
void AdbBridge::Start()
{
	LOG("[AdbBride] Starting adb");
	AdbBridge::RunCommand("/usr/bin/adb start-server");
}

/**
 *
 */
void AdbBridge::Stop()
{
	LOG("[AdbBride] Stopping adb");
	AdbBridge::RunCommand("/usr/bin/adb kill-server");
}

/**
 *
 */
void AdbBridge::RestartAdb()
{
	LOG("[AdbBride] Restarting adb");
	AdbBridge::Stop();
	AdbBridge::Start();
}

/**
 *
 */
void AdbBridge::PortForward(int local_port, int remote_port)
{
	AdbBridge::RunCommand(("/usr/bin/adb forward tcp:" + std::to_string(local_port) + " tcp:" + std::to_string(remote_port)).c_str());
}

/**
 *
 */
void AdbBridge::ReversePortForward(int remote_port, int local_port)
{
	AdbBridge::RunCommand(("/usr/bin/adb reverse tcp:" + std::to_string(remote_port) + " tcp:" + std::to_string(local_port)).c_str());
}

/**
 *
 */
void AdbBridge::RestartApp()
{
	LOG("[AdbBride] Restarting app");
	AdbBridge::RunCommand("/usr/bin/adb shell am force-stop com.team254.cheezdroid \\; am start com.team254.cheezdroid/com.team254.cheezdroid.VisionTrackerActivity");
}
