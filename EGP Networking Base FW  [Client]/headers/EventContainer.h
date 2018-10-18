#pragma once
#include "Event.h"


struct node
{
	node(Event* d, node* n)
	{
		data = d; 
		next = n;
	}
	Event* data;
	node *next;
};

class EventContainer
{
private:
	node* mStart;
	node* mEnd;
	int eventQueueLength = 0;
public:
	void addEvent(Event *newEvent)
	{
		//add event to the queue
		node *newNode = new node(newEvent,mStart);
		newNode->data = newEvent;
		eventQueueLength++;

		if (mStart == NULL)
		{
			mStart = newNode;
			mEnd = newNode;
		}
		else
		{
			mEnd->next = newNode;
			mEnd = newNode;
		}
	}
	void executeNext()
	{
		if (mStart != NULL)
		{
			//remove first event from queue
			node *tmp;

			tmp = mStart;
			mStart = mStart->next;
			tmp->next = NULL;

			if (mStart == NULL)
				mEnd = NULL;
			//execute event
			tmp->data->execute();
			delete tmp;
		}
	}
};