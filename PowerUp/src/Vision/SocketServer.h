#ifndef _SOCKETSERVER_H_
#define _SOCKETSERVER_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <signal.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define NO_SOCKET -1

#define SENDER_MAXSIZE 128
#define DATA_MAXSIZE 512

// message --------------------------------------------------------------------

typedef struct {
  char sender[SENDER_MAXSIZE];
  char data[DATA_MAXSIZE];
}  message_t;

// message queue --------------------------------------------------------------

typedef struct {
  int size;
  message_t *data;
  int current;
} message_queue_t;

// peer -----------------------------------------------------------------------

typedef struct {
  int socket;
  struct sockaddr_in addres;

  /* Messages that waiting for send. */
  message_queue_t send_buffer;

  /* Buffered sending message.
   *
   * In case we doesn't send whole message per one call send().
   * And current_sending_byte is a pointer to the part of data that will be send next call.
   */
  message_t sending_buffer;
  size_t current_sending_byte;

  /* The same for the receiving message. */
  message_t receiving_buffer;
  size_t current_receiving_byte;
} peer_t;

/**
 *
 */
class SocketServer
{
public:
	SocketServer();
	virtual ~SocketServer();
	void ShutdownProperly(int code);

private:
	void HandleSignalAction(int sig_number);
	int SetupSignals();

	int listen_sock;
	peer_t connection_list[MAX_CLIENTS];
};

#endif
