#include "SocketServer.h"
#include "../Utilities/Log.h"

/**
 *
 */
SocketServer::SocketServer()
{
}

/**
 *
 */
SocketServer::~SocketServer()
{
}

/**
 *
 */
void HandleSignalAction(int sig_number)
{
	if (sig_number == SIGINT)
	{
		LOG("[SocketServer] SIGINT was caught");
//		SocketServer::ShutdownProperly(EXIT_SUCCESS);
	}
	else if (sig_number == SIGPIPE)
	{
		LOG("[SocketServer] SIGPIPE was caught");
//		SocketServer::ShutdownProperly(EXIT_SUCCESS);
	}
}

/**
 *
 */
int SocketServer::SetupSignals()
{
	struct sigaction sa;
//	sa.sa_handler = HandleSignalAction;
	if (sigaction(SIGINT, &sa, 0) != 0)
	{
		LOG("[SocketServer] sigaction()");
		return -1;
	}
	if (sigaction(SIGPIPE, &sa, 0) != 0)
	{
		LOG("[SocketServer] sigaction()");
		return -1;
	}

	return 0;
}

/**
 *
 */
void SocketServer::ShutdownProperly(int code)
{
	int i;

	close(listen_sock);

	for (i=0; i<MAX_CLIENTS; i++)
		if (connection_list[i].socket != NO_SOCKET)
			close(connection_list[i].socket);

	LOG("[SocketServer] Shutdown server properly");

	return;
}
