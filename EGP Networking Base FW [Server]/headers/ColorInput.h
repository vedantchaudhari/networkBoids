#pragma once

char getColor(std::string &s)
{
	if (_kbhit())
	{
		char c = _getch();
		if (c == 13)
		{
			if (atoi(s.c_str()) < 17 && atoi(s.c_str()) > 0)
				return NEWCOL;
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