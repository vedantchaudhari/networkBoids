#pragma once

//getch and kbhit
#include <conio.h>
#include "CommonInclude.h"

enum Commands
{
	ENTER = '\n',
	LEAVE = 1,
	COLOR,
	INVALID_COLOR,
	NEWCOL
};

char getInput(std::string &s)
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == 13)
		{
			if (s == "/l")
			{
				return LEAVE;
			}
			if (s == "/c")
			{
				printf("\n");
				return COLOR;
			}
			printf("\n");
			return '\n';
		}
		else if (c == '\b') //backspace
		{
			if (s.length()) //check for content to backspace
			{
				s.pop_back(); //remove last char from buffer
				printf("\b \b"); //change display on screen
			}
		}
		else if (c != NULL)
		{
			s += c;
			printf("%c", c);
		}
		return c;
	}
	return 0;
}

char getColor(std::string &s)
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == 13)
		{
			if (atoi(s.c_str()) < 17 && atoi(s.c_str()) > 0)
				return NEWCOL;
			else
			{
				s.clear();
				return INVALID_COLOR;
			}
			printf("\n");
			return '\n';
		}
		else if (c == '\b') //backspace
		{
			if (s.length()) //check for content to backspace
			{
				s.pop_back(); //remove last char from buffer
				printf("\b \b"); //change display on screen
			}
		}
		else if (c != NULL)
		{
			s += c;
			printf("%c", c);
		}
		return c;
	}
	return 0;
}