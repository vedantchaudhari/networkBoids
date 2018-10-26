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
	PUSH = ID_USER_PACKET_ENUM + 1,
	SETMODE_PUSH,
	SETMODE_SHARE,
	SETMODE_COUPLED
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
		iTime2 = SDL_GetTicks();

		if (iTime2 - iTime >= TICK) {
			iTime = SDL_GetTicks();
			flock.update();
		}

		flock.render();
		update();
	}

	SDLInterface::getInstance()->exit();
	return 0;
}