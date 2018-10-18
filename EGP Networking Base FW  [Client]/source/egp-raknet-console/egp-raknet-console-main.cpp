/*
RakNet Console Application
Prepared by Dan Buckstein
September 5, 2018

Simple RakNet application following official tutorials.

****TO-DO: add your own implementations and comments

Resources:
http://www.jenkinssoftware.com/raknet/manual/tutorialsample1.html
http://www.jenkinssoftware.com/raknet/manual/tutorialsample2.html
http://www.jenkinssoftware.com/raknet/manual/tutorialsample3.html

http://www.raknet.net/raknet/manual/creatingpackets.html
http://www.raknet.net/raknet/manual/receivingpackets.html
http://www.raknet.net/raknet/manual/sendingpackets.html
http://www.raknet.net/raknet/manual/timestamping.html

Read them for the secrets to success!
E.g. pointers on pointers ;)


This file was modified by Jack Malvey with permission from author.”
"I certify that this work is
entirely my own. The assessor of this project may reproduce this project
and provide copies to other academic staff, and/or communicate a copy of
this project to a plagiarism-checking service, which may retain a copy of the
project on its database"
-John Malvey 1005854
*/
#include "../headers/CommonInclude.h"
#include "../headers/ColorEvent.h"
#include "../headers/ChatEvent.h"
#include "../headers/ConnectEvent.h"
#include "../headers/MessageInput.h"

//keep track of IP addresses and names
#pragma pack(push, 1)
struct User
{
	RakNet::SystemAddress IP;
	RakNet::TimeMS timeStamp;
	bool isConnected = false;
	bool inGame = false;
};
#pragma pack(pop)


// entry function
int main(int const argc, char const *const *const argv)
{
	//Initializations
	const unsigned int bufferSz = 512;
	char str[bufferSz];
	unsigned short serverPort = 60000;

	//Begin Networking
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();

	//set up client
	RakNet::SocketDescriptor sd;
	peer->Startup(1, &sd, 1);

	//connect client and server
	printf("Enter server IP or hit enter for 127.0.0.1\n");
	fgets(str, 512, stdin);
	if (str[0] == '\n') {
		strcpy(str, "127.0.0.1");
	}

	system("cls");
	printf("Starting the client.\n");
	peer->Connect(str, serverPort, 0, 0);

	//peer->SetTimeoutTime(999999, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	RakNet::Packet *packet;
	while (1)
	{
		for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive())
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				printf("Our connection request has been accepted.\n");
				//send message server that a user joined
				GameMessageData connectConfirmation;
				connectConfirmation.ID = ID_ADD_CONNECT_EVENT;
				peer->Send((char*)&connectConfirmation, sizeof(connectConfirmation), HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
			}
			break;
			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
				break;

			case ID_DISCONNECTION_NOTIFICATION:

				printf("We have been disconnected.\n");

			case ID_CONNECTION_LOST:
				printf("Connection lost.\n");
				break;
			case ID_LOCAL_PRINT:
			{
				GameMessageData* gameMessage = (GameMessageData*)packet->data;
				printf("%s\n", gameMessage->msg);
			}
			break;

			default:
				printf("Message with identifier %i has arrived.\n", packet->data[0]);
				break;
			}
		}

	}
	// shut down networking by destroying peer interface instance
	RakNet::RakPeerInterface::DestroyInstance(peer);

	// exit
	printf("\n\n");
	system("pause");
	return 0;
}
