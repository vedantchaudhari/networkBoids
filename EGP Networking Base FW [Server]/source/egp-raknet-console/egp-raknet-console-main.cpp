/*
	RakNet Console Application
	Prepared by Dan Buckstein
	September 5, 2018

	This file was modified by Jack Malvey with permission from author.”
	"I certify that this work is
	entirely my own. The assessor of this project may reproduce this project
	and provide copies to other academic staff, and/or communicate a copy of
	this project to a plagiarism-checking service, which may retain a copy of the
	project on its database"
	-John Malvey 1005854
*/
#include "../headers/CommonInclude.h"


// entry function
int main(int const argc, char const *const *const argv)
{
	//Initializations
	const unsigned int bufferSz = 512;
	char str[bufferSz];
	unsigned short serverPort = 60000;
	const unsigned int MAX_CLIENTS = 3;

	GameMessageData serverName;

	//Begin Networking
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();

	//set up server
	printf("Set Server Name:\n");
	fgets(str, 512, stdin);
	str[strcspn(str, "\n")] = 0;//GET RID OF UNCESSARY NEW LINE
	strcpy(serverName.msg, str);


	RakNet::SocketDescriptor sd(serverPort, 0);
	peer->Startup(MAX_CLIENTS, &sd, 1);

	//connect client and server
	printf("Starting the server @ %s.\n", peer->GetLocalIP(2));
	peer->SetMaximumIncomingConnections(MAX_CLIENTS);

	peer->SetTimeoutTime(999999, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
	std::string placeHolder = "";
	RakNet::Packet *packet;
	while (1)
	{

		for (
			packet = peer->Receive();
			packet;
			peer->DeallocatePacket(packet), packet = peer->Receive()
			)
		{
			switch (packet->data[0])
			{
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
				printf("Another client has disconnected.\n");
				break;
			case ID_REMOTE_CONNECTION_LOST:
				printf("Another client has lost the connection.\n");
				break;
			case ID_NEW_INCOMING_CONNECTION:
				printf("A client has connected.\n");
				break;
			case ID_REMOTE_NEW_INCOMING_CONNECTION:
				printf("Another client has connected.\n");
				break;

			case ID_DISCONNECTION_NOTIFICATION:
				printf("A client has disconnected.\n");
				break;

			case ID_CONNECTION_LOST:
				printf("A client lost the connection.\n");
				break;
			case ID_LOCAL_PRINT:
			{
				GameMessageData* gameMessage = (GameMessageData*)packet->data;
				printf("%s\n", gameMessage->msg);
			}
			break;

			case ID_SEND_TO_ALL_FROM_SERVER:
			{
				GameMessageData* temp;
				temp = (GameMessageData*)packet->data;
				GameMessageData gameMessage = *temp;
				gameMessage.ID = ID_LOCAL_PRINT;

				printf(gameMessage.msg, "\n");

				printf("\n");
				peer->Send((char*)&gameMessage, sizeof(gameMessage), HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

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
	
