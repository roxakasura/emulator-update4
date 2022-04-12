#include "stdafx.h"
#include "Testando.h"

BOOL IsBadFileLine(char *FileLine,int &Flag)
{
	if(Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			Flag = FileLine[0] - 48;

			return true;
		}
	}
	else if(Flag < 0 || Flag > 9)
	{
		Flag = 0;
	}

	if(!strncmp(FileLine,"end", 3))
	{
		Flag = 0;

		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
	{
		return true;
	}

	size_t lengthfile = strlen(FileLine);

	for(UINT i = 0; i < lengthfile; i++)
	{
		if(isalnum(FileLine[i]))
		{
			return false;
		}
	}

	return true;
}