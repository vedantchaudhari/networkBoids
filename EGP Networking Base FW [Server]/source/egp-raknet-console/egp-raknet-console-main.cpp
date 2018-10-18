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
};
#pragma pack(pop)





// entry function
int main(int const argc, char const *const *const argv)
{
	//Initializations
	const unsigned int bufferSz = 512;
	char str[bufferSz];
	unsigned short serverPort = 60000;
	const unsigned int MAX_CLIENTS = 2;

	GameMessageData serverName;

	User* userList;


	//Begin Networking
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();

	//set up server
	printf("Set Server Name:\n");
	fgets(str, 512, stdin);
	str[strcspn(str, "\n")] = 0;//GET RID OF UNCESSARY NEW LINE
	strcpy(serverName.msg, str);


	RakNet::SocketDescriptor sd(serverPort, 0);
	peer->Startup(MAX_CLIENTS, &sd, 1);
	userList = new User[MAX_CLIENTS];

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
			case ID_NEW_INCOMING_CONNECTION:
				for (unsigned int i = 0; i < MAX_CLIENTS; i++)
				{
					if (!userList[i].isConnected)
					{
						userList[i].IP = packet->systemAddress;
						userList[i].isConnected = true;
						userList[i].timeStamp = RakNet::GetTimeMS();
						break;
					}
					GameMessageData textOut;
					strcpy(textOut.msg, "Welcome to ");
					strcat(textOut.msg, serverName.msg);
					strcat(textOut.msg, "!\ntype /help for a list of commands\n");
					peer->Send((char*)&textOut, sizeof(textOut), HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
				}
				break;

			case ID_NO_FREE_INCOMING_CONNECTIONS:
				printf("The server is full.\n");
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

				if (placeHolder.size() > 0) //check if there's anything currently in the buffer
				{
					printf("\33[2K\r"); //clear what's currently on the line
					printf("%s\n", gameMessage->msg);
					printf(placeHolder.c_str()); //print what was there on the next line
				}
				else
					printf("%s\n", gameMessage->msg);
			}
			break;

			//only server will ever run this scenario
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
		switch (getInput(placeHolder))
		{
			//Public Messages
		case ENTER:
		{
			///***********
			///TO-DO:
			///Implement data mode changes via console
			///***********

			/*GameMessageData ChatMessage;
			if (isServer)
				ChatMessage.ID = ID_LOCAL_PRINT;
			else
				ChatMessage.ID = ID_SEND_TO_ALL_FROM_SERVER;

			strcpy(ChatMessage.msg, screenName.msg);

			strcat(ChatMessage.msg, ": ");
			strcat(ChatMessage.msg, placeHolder.c_str());

			DataStructures::List<RakNet::SystemAddress> sys;
			DataStructures::List<RakNet::RakNetGUID> guids;

			peer->GetSystemList(sys, guids);
			peer->Send((char*)&ChatMessage, sizeof(ChatMessage), HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
			*/
			placeHolder.clear();
		}
		break;
		default:
			break;
		}


	}

	// shut down networking by destroying peer interface instance
	RakNet::RakPeerInterface::DestroyInstance(peer);

	// exit
	printf("\n\n");
	system("pause");
	return 0;
}
