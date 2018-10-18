#pragma once
#include "Event.h"
#include "CommonInclude.h"
class ColorEvent : public Event
{
public:
	ColorEvent();
	ColorEvent(int color, RakNet::SystemAddress to);
	void execute() 
	{
		
		//send message to client to change color
		GameMessageData colInfo;
		colInfo.color = mColor;

		colInfo.ID = ID_CHANGE_COLOR;
		
		
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, mColor);
		///DEBUG
		/*char buff[2];
		printf(_itoa(mColor, buff, 10));
		printf("\n");*/
	}

private:
	int mColor;
	RakNet::SystemAddress mSendTo;
};