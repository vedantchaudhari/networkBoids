#pragma once
#ifndef EVENT
#define EVENT
enum EVENT_ID
{
	INVALID_EVENT = -1,
	CONNECT_EVENT,
	CHAT_EVENT,
	COLOR_EVENT

};

class Event
{
public:
	Event();
	Event(EVENT_ID id);
	virtual ~Event();

	virtual void execute() = 0;
private:
	EVENT_ID mID;
};
#endif // !EVENT
