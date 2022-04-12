#include "stdafx.h"
#include "SelectCharAnimation.h"
#include "ItemManager.h"
#include <time.h>
#include "Util.h"

cSelectChar gSelectChar;

void cSelectChar::Load()
{
	srand((unsigned)time(NULL));

	SetCompleteHook(0xE8, oOnCharClick_Call, &this->OnCharClick);
};

int cSelectChar::OnCharClick(DWORD This)
{
	if (oSelectedCharView != -1)
	{
		DWORD ObjectPreview = *(DWORD*)(0x074D2B28) + (oSelectedCharView * 0x47C);
		short ObjectPetSlot = *(short*)(ObjectPreview + 848);

		switch (ObjectPetSlot)
		{
		case GET_ITEM_MODEL(13, 2): // Horn of Uniria
		case GET_ITEM_MODEL(13, 3): // Horn of Dinorant
		{
			int Random = (rand() % 2) ? AT_GALLOPINGATTACK7 : ((rand() % 2) ? AT_GALLOPINGATTACK8 : AT_GALLOPINGATTACK9);

			pActionSend(ObjectPreview, Random);
			break;
		}
		case GET_ITEM_MODEL(13, 4): // Dark Horse
		{
			int Random = (rand() % 2) ? AT_GALLOPINGACTION5 : ((rand() % 2) ? AT_GALLOPINGACTION6 : AT_GALLOPINGACTION1);

			if (Random == AT_GALLOPINGACTION5)
			{
				for (int i = 0; i < 5; i++)
				{
					if (i != oSelectedCharView)
					{
						DWORD TempObjectPreview = *(DWORD*)(0x074D2B28) + (i * 0x47C);
						short TempObjectPetSlot = *(short*)(TempObjectPreview + 848);

						if (TempObjectPreview)
						{
							if (TempObjectPetSlot == -1)
							{
								pActionSend(TempObjectPreview, AT_FALL1);
							}
						}
					}
				}
			}

			pActionSend(ObjectPreview, Random);
			break;
		}
		case GET_ITEM_MODEL(13, 37): // Fenrir
		{
			int Action[] = { AT_FENRIRATTACK1, AT_FENRIRATTACK4, AT_FENRIRACTION2 };

			pActionSend(ObjectPreview, Action[rand() % 3]);
			break;
		}
		default: // None
		{
			int Action[] =
			{
				AT_ATTACK13,
				AT_ATTACK15,
				AT_ATTACK18,
				AT_ATTACK19,
				AT_ATTACK20,
				AT_ATTACK24,
				AT_ATTACK31,
				AT_ATTACK40,
				AT_GREETING1,
				AT_GOODBYE2,
				AT_CLAP1,
				AT_CHEER1,
				AT_GESTURE1,
				AT_NEGATE1,
				AT_WIN1,
				AT_AGAIN1,
				AT_SALUTE1,
				AT_STRETCHING,
				AT_STRETCHING2,
				AT_FUCKING,
				AT_COMEON,
				AT_LOOK,
				AT_CELEBRATING1,
				AT_CELEBRATING3,
				AT_CELEBRATING4,
				AT_DIE1,
				AT_DIE2,
				AT_JUMPING
			};

			pActionSend(ObjectPreview, Action[rand() % 28]);
			break;
		}
		}
	}

	return pOnCharClick(This);
}