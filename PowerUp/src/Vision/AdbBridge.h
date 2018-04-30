#ifndef _VISION_ADBBRIDGE_HG_
#define _VISION_ADBBRIDGE_HG_

class AdbBridge
{
public:
	AdbBridge();
	virtual ~AdbBridge();
	void Start(void);
	void Stop(void);
	void RestartAdb(void);
	void PortForward(int local_port, int remote_port);
    void ReversePortForward(int remote_port, int local_port);
    void RestartApp(void);

private:
	bool RunCommand(const char* cmd);
};

#endif
