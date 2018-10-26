#pragma once


// standard includes
#include <stdio.h>
#include <string.h>
#include <string>

// RakNet includes
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"

//boids includes
#include "Define.h"
#include "Flock.h"

enum GameMessages
{
	SETMODE_PUSH = ID_USER_PACKET_ENUM+1,
	SETMODE_SHARE,
	SETMODE_COUPLED,
	DATA_PUSH,
	DATA_SHARE,
	DATA_COUPLED,
	INCOMING_CLIENTDATA,
	ID_SEND_TO_ALL_FROM_SERVER,
};

#pragma pack(push, 1)
struct GameMessageData
{
	int ID = DATA_PUSH;
	Flock flockData = NULL;
};
#pragma pack(pop)
#pragma pack(push, 1)
struct ClientData
{
	int ID = INCOMING_CLIENTDATA;
	Flock clientFlock = Flock(NUM_BOIDS);
	RakNet::SystemAddress clientIP;
	bool instantiated = false;
};
#pragma pack(pop)
