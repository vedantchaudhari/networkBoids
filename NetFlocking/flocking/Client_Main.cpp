// Certificate of Authenticity
//
// EGP-405-01 Networking for Online Games
// Project 2 & Lab 4
// 10-30-2018
//
// Vedant Chaudhari, 1532077
// John Malvey
//
// We certify that this work is entirely our own.The assessor of this project may reproduce this project 
// and provide copies to other academic staff, and/or communicate a copy of this project to a plagiarism 
// - checking service, which may retain a copy of the project on its database.

// Based on https://github.com/forsythe/boids

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <vector>

#include "Define.h"
#include "Flock.h"
#include "SDLInterface.h"
#include "InputInterface.h"

#include "../../DevSDKs/include/RakNet/RakPeerInterface.h"
#include "../../DevSDKs/include/RakNet/MessageIdentifiers.h"
#include "../../DevSDKs/include/RakNet/BitStream.h"
#include "../../DevSDKs/include/RakNet/RakNetTypes.h"
#include <stdio.h>

enum GameMessages
{
	SETMODE_PUSH= ID_USER_PACKET_ENUM + 1,
	SETMODE_SHARE,
	SETMODE_COUPLED,
	DATA_PUSH,
	DATA_SHARE,
	DATA_COUPLED,
	SEND_CLIENTDATA
};

struct ClientData
{
	int ID = SEND_CLIENTDATA;
	Flock clientFlock = NULL;
	RakNet::SystemAddress clientIP;
};

enum dataMode
{
	PUSH_MODE,
	SHARE_MODE,
	COUPLED_MODE,
};

void update() {
	SDLInterface::getInstance()->render();
	SDLInterface::getInstance()->background();
	InputInterface::getInstance()->update();
	SDLInterface::getInstance()->setColor(255, 255, 255, 255);
}

int main(int argc, char *argv[]) {
	SDLInterface::getInstance()->init(WIDTH, HEIGHT, TITLE);
	Flock flock = Flock(NUM_BOIDS);

	Uint32 iTime = SDL_GetTicks();
	Uint32 iTime2 = 0;

	//networking vars
	RakNet::Packet *packet;
	RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
	const short SERVERPORT = 60000;
	char str[512];
	RakNet::SocketDescriptor sd;

	//network modes
	int dataMode = PUSH_MODE;

	peer->Startup(1, &sd, 1);

	//set up client connection to server
	printf("Enter server IP\n");
	fgets(str, 512, stdin);
	if (str[0] == 10) {
		strcpy(str, "127.0.0.1");
	}

	system("cls");
	peer->Connect(str, SERVERPORT, 0, 0);

	//big timeout timer
	peer->SetTimeoutTime(999999, RakNet::UNASSIGNED_SYSTEM_ADDRESS);


	
	while (SDLInterface::getInstance()->isExit == false) {
		
		//recieve network packets
		for (
			packet = peer->Receive();
			packet; 
			peer->DeallocatePacket(packet), packet = peer->Receive()
			)
		{
			switch (packet->data[0])
			{
			case SETMODE_PUSH:
			{
				dataMode = PUSH_MODE;
			}
			break;
			case SETMODE_SHARE:
			{
				dataMode = PUSH_MODE;
			}
			break;
			case SETMODE_COUPLED:
			{
				dataMode = COUPLED_MODE;
			}
			break;
			case SEND_CLIENTDATA:
			{

				printf("data sent\n");
				//send out client data to server
				// ****TODO Probably load the flock up with boids before it's connected to the server
				ClientData sendData;
				sendData.clientFlock = flock;
				//sendData.clientFlock.boids = flock.boids;
				sendData.ID = SEND_CLIENTDATA;
				peer->Send((char*)&sendData, sizeof(sendData), HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
			}
			break;

			}
		}
			//run local boids
			
			iTime2 = SDL_GetTicks();

			if (iTime2 - iTime >= TICK) {
				iTime = SDL_GetTicks();
				flock.update();
			}
			

			// send data to server
			switch (dataMode)
			{
			case PUSH_MODE:
			{

			}
			break;
			case SHARE_MODE:
			{

			}
			break;
			case COUPLED_MODE:
			{

			}
			break;
			}

			flock.render();
			update();
		}
	
	SDLInterface::getInstance()->exit();
	return 0;
}