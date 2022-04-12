#include "StdAfx.h"

cSelectChar gSelectChar;

void cSelectChar::Load()
{
	srand((unsigned)time(NULL));
	gToolKit.SetOp((LPVOID)oOnCharClick_Call, this->OnCharClick, ASM::CALL);
}

char cSelectChar::OnCharClick()
{
	if (gSelectChar.LastCharacter != oSelectedCharView)
	{
		int ObjectStruct = *(DWORD*)0x7424644 + 1060 * oSelectedCharView;
		
		switch (*(WORD*)(ObjectStruct+776))
	    {
			case GET_ITEM_MODEL(13,2): // Horn of Uniria
            case GET_ITEM_MODEL(13,3): // Horn of Dinorant
		    {
				int DinoAction[] = {AT_GALLOPINGATTACK2,AT_GALLOPINGACTION6};
				pActionSend(ObjectStruct, DinoAction[rand() % 2]); //AT_GALLOPINGACTION6, AT_GALLOPINGATTACK2
		    }
			break;
			case GET_ITEM_MODEL(13,4): // Dark Horse
			{
				//int Random = (rand() % 2) ? AT_GALLOPINGACTION5 : ((rand() % 2) ? AT_GALLOPINGACTION6 : AT_GALLOPINGACTION1);
				pActionSend(ObjectStruct,AT_GALLOPINGACTION1);
			}
			break;
		    default: 
			int Action[] =
			{
				113,114,115,116,117,118,120,121,123,
				124,127,129,133,134,137,140,141,142,
				143,145,146,148,152,156,158,160,161,
			};				
			   pActionSend(ObjectStruct,Action[rand() % 27]);
		}
	

		gSelectChar.LastCharacter = oSelectedCharView;
	}
	return pOnCharClick();
}
