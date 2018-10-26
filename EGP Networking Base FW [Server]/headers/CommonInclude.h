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


enum GameMessages
{
	SETMODE_PUSH = ID_USER_PACKET_ENUM,
	SETMODE_SHARE,
	SETMODE_COUPLED,
	ID_LOCAL_PRINT,
	ID_SEND_TO_ALL_FROM_SERVER,
	ID_GAME_MESSAGE_1,
};

#pragma pack(push, 1)
struct GameMessageData
{
	int ID = ID_LOCAL_PRINT;
	char msg[512];
	int color;
	RakNet::SystemAddress sendLoc;
};
#pragma pack(pop)
