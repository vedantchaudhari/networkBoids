#pragma once


// standard includes
#include <stdio.h>
#include <string.h>
#include <string>

//custom include
#include "EventContainer.h"
// RakNet includes
#include "RakNet/RakPeerInterface.h"
#include "RakNet/MessageIdentifiers.h"
#include "RakNet/RakNetTypes.h"
#include "RakNet/BitStream.h"
#include "RakNet/GetTime.h"


enum GameMessages
{
	ID_LOCAL_PRINT = ID_USER_PACKET_ENUM,
	ID_SEND_TO_ALL_FROM_SERVER,
	ID_INCOMING_NAME,
	ID_ADD_CONNECT_EVENT,
	ID_ADD_COLOR_EVENT, ID_CHANGE_COLOR,
	ID_ADD_CHAT_EVENT,
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
