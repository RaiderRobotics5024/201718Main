#include "SocketServer.h"
#include "../Utilities/Log.h"
#include "messages/OffWireMessage.h"
#include "messages/HeartbeatMessage.h"
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

/**
 *
 */
SocketServer::SocketServer()
{
	this->pTimer = new Timer();
	SocketServer::Setup();
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
bool SocketServer::Setup()
{
    //initialise all client_socket[] to 0 so not checked
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client_socket[i] = 0;
    }

    // Creating socket file descriptor
    if ((master_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        LOG("[SocketServer] socket failed");
        return false;
    }

    // Forcefully attaching socket to the port
    if (setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
    	LOG("[SocketServer] setsockopt");
        return false;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
    	LOG("[SocketServer] bind failed");
        return false;
    }

    if (listen(master_socket, 3) < 0)
    {
    	LOG("[SocketServer] listen");
        return false;
    }

    LOG("[SocketServer] Waiting for connections...");

    return true;
}

/**
 *
 */
void SocketServer::Accept()
{
    addrlen = sizeof(address);

    while(1)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for (int i = 0 ; i < MAX_CLIENTS ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select(max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            LOG("[SocketServer] select error");
        }

        //If something happened on the master socket, then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
            {
            	LOG("[SocketServer] accept failure");
                return;
            }

            //inform user of socket number - used in send and receive commands
            LOG("[SocketServer] New connection , socket fd: " << new_socket << ", ip:" << inet_ntoa(address.sin_addr) << ", port: " << ntohs (address.sin_port));

            //add new socket to array of sockets
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    LOG("[SocketServer] Adding to list of sockets as " << i);

                    break;
                }
            }
        }

        SocketServer::Read();
    }

    return;
}

/**
 *
 */
void SocketServer::Read()
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        sd = client_socket[i];

        if (FD_ISSET(sd , &readfds))
        {
            //Check if it was for closing, and also read the incoming message
            if ((valread = read(sd , buffer, 2048)) == 0)
            {
                //Somebody disconnected , get his details and print
                getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                LOG("[SocketServer] Host disconnected , ip: " << inet_ntoa(address.sin_addr) << ", port: " << ntohs(address.sin_port));

                //Close the socket and mark as 0 in list for reuse
                close(sd);
                client_socket[i] = 0;
            }

            //Echo back the message that came in
            else
            {
            	this->dLastMessageReceivedTime = pTimer->GetFPGATimestamp();

                //set the string terminating NULL byte on the end of the data read
                buffer[valread] = '\0';
//                LOG("[SocketServer] Buffer: " << buffer);

        		std::stringstream ss(buffer);
        		std::string message;

        		while (std::getline(ss, message, '\n'))
        		{
        			OffWireMessage* pMessage = new OffWireMessage(message);
        			if (pMessage->IsValid()) {
        				SocketServer::HandleMessage(pMessage, 0.0);
        			}
        		}
            }
        }
    }

    return;
}

/**
 *
 */
double SocketServer::GetLastMessageReceivedTime()
{
	return this->dLastMessageReceivedTime;
}

/**
 *
 */
void SocketServer::HandleMessage(OffWireMessage* message, double timestamp)
{
    if (message->GetType().compare("heartbeat") == 0)
    {
        Send(HeartbeatMessage::GetInstance());
    }
    else
    {
    	LOG("[SocketSever] Not heartbeat..." << message->GetType());
    }


}

/**
 *
 */
void SocketServer::Send(HeartbeatMessage* message)
{
	std::string toSend = message->ToJson() + "\n";

    send(new_socket, &toSend, toSend.length() , 0);

//    LOG("[SocketServer] Message sent");

    return;

}
