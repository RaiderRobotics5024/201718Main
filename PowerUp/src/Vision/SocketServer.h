#ifndef _SOCKETSERVER_H_
#define _SOCKETSERVER_H_

#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <Timer.h>
#include "messages/OffWireMessage.h"
#include "messages/HeartbeatMessage.h"

#define MAX_CLIENTS 30
#define PORT 8254

/**
 *
 */
class SocketServer
{
public:
	SocketServer();
	virtual ~SocketServer();
	void Accept(void);
	double GetLastMessageReceivedTime();

private:
	void HandleMessage(OffWireMessage* message, double timestamp);
	bool Setup(void);
	void Read(void);
	void Send(HeartbeatMessage* message);

	Timer* pTimer;
	double dLastMessageReceivedTime = 0.0;

    int opt = 1;
    int client_socket[MAX_CLIENTS];
    int master_socket, max_sd, sd, activity, addrlen;
    fd_set readfds;

    int server_fd, new_socket, valread;

    struct sockaddr_in address;
    char buffer[2048] = {0};
};

#endif
