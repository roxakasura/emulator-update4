#include "stdafx.h"

cItem gcItem;

void cItem::ItemLoad()
{
	SetCompleteHook(0xE9,0x00540A50,&ItemConvert);
	SetByte(0x00506FAD+1,0x8C);
	SetByte(0x005F9CC2+2,0x10);
}

void ItemConvert(int ObjectItem, BYTE Attribute1, BYTE Attribute2, BYTE Attribute3)
{
	*(DWORD*)(ObjectItem + 4) = Attribute1;

	int Level = (Attribute1 >> 3) & 15;
	int Excel = Attribute2 & 63;
	bool ExtOption = false;
	int ExcelAddValue = 0;

	if ((*(WORD*)ObjectItem >= GET_ITEM(12,3) && *(WORD*)ObjectItem <= GET_ITEM(12,512))
		|| *(WORD*)ObjectItem == GET_ITEM(0,19)
		|| *(WORD*)ObjectItem == GET_ITEM(4,18)
		|| *(WORD*)ObjectItem == GET_ITEM(5,10)
		|| *(WORD*)ObjectItem == GET_ITEM(2,13)
		|| *(WORD*)ObjectItem == GET_ITEM(13,30)) 
    {
        Excel = 0;
    }

	if ((Attribute3 % 0x4) == 1 || (Attribute3 % 0x4) == 2)
    {
        Excel = 1;
        ExtOption = true;
    }

	int ItemAttribute = *(DWORD*)0x773D118 + 80 * *(WORD*)ObjectItem;

	*(BYTE*)(ObjectItem + 10) = *(BYTE*)(ItemAttribute + 30);	  //Item->TwoHand			
	*(BYTE*)(ObjectItem + 23) = *(BYTE*)(ItemAttribute + 41);	  //Item->WeaponSpeed		
    *(WORD*)(ObjectItem + 12) = *(BYTE*)(ItemAttribute + 36);	  //Item->DamageMin			
	*(WORD*)(ObjectItem + 14) = *(BYTE*)(ItemAttribute + 37);	  //Item->DamageMax			
	*(BYTE*)(ObjectItem + 16) = *(BYTE*)(ItemAttribute + 38);	  //Item->SuccessfulBlocking
	*(WORD*)(ObjectItem + 18) = *(BYTE*)(ItemAttribute + 39);	  //Item->Defense			
	*(WORD*)(ObjectItem + 20) = *(BYTE*)(ItemAttribute + 40);	  //Item->MagicDefense		
	*(WORD*)(ObjectItem + 24) = *(BYTE*)(ItemAttribute + 42);	  //Item->WalkSpeed			
	*(BYTE*)(ObjectItem + 22) = *(BYTE*)(ItemAttribute + 45);	  //Item->MagicPower		

	int SetItemDropLevel = *(BYTE*)(ItemAttribute + 31) + 30;

	if (*(BYTE*)(ItemAttribute + 36)) // -> DamageMin
	{
		if (Excel > 0 && *(BYTE*)(ItemAttribute + 31))
		{
			if (ExcelAddValue)
			{
				*(WORD*)(ObjectItem + 12) += ExcelAddValue;
			}
			else
			{
				*(WORD*)(ObjectItem + 12) += *(BYTE*)(ItemAttribute + 36) * 25 / *(BYTE*)(ItemAttribute + 31) + 5;
			}
		}

		if (ExtOption)
        {
            *(WORD*)(ObjectItem + 12) += 5 + (SetItemDropLevel / 40);
        }

		*(WORD*)(ObjectItem + 12) += (min(9, Level) * 3);

		switch(Level - 9)
		{
		case 6: *(WORD*)(ObjectItem + 12) += 9;	// +15
		case 5: *(WORD*)(ObjectItem + 12) += 8;	// +14
		case 4: *(WORD*)(ObjectItem + 12) += 7;	// +13
		case 3: *(WORD*)(ObjectItem + 12) += 6;	// +12
		case 2: *(WORD*)(ObjectItem + 12) += 5;	// +11
		case 1: *(WORD*)(ObjectItem + 12) += 4;	// +10
		default: break;
		};
	}

	if (*(BYTE*)(ItemAttribute + 37)) // -> DamageMax
	{
		if (Excel > 0 && *(BYTE*)(ItemAttribute + 31))
		{
			if (ExcelAddValue)
			{
				*(WORD*)(ObjectItem + 14) += ExcelAddValue;
			}
			else
			{
				*(WORD*)(ObjectItem + 14) += *(BYTE*)(ItemAttribute + 36) * 25 / *(BYTE*)(ItemAttribute + 31) + 5;
			}
		}

        if (ExtOption)
        {
            *(WORD*)(ObjectItem + 14) += 5 + (SetItemDropLevel / 40);
        }

        *(WORD*)(ObjectItem + 14) += (min(9, Level) * 3);

		switch (Level - 9)
		{
		case 6: *(WORD*)(ObjectItem + 14) += 9;	// +15
		case 5: *(WORD*)(ObjectItem + 14) += 8;	// +14
		case 4: *(WORD*)(ObjectItem + 14) += 7;	// +13
		case 3: *(WORD*)(ObjectItem + 14) += 6;	// +12
		case 2: *(WORD*)(ObjectItem + 14) += 5;	// +11
		case 1: *(WORD*)(ObjectItem + 14) += 4;	// +10
		default: break;
		};
	}

	if (*(BYTE *)(ItemAttribute + 45)) // -> MagicPower
	{
		if (Excel > 0 && *(BYTE*)(ItemAttribute + 31))
		{
			if (ExcelAddValue)
			{
				*(BYTE*)(ObjectItem + 22) += ExcelAddValue;
			}
			else
			{
				*(BYTE*)(ObjectItem + 22) += *(BYTE*)(ItemAttribute + 45) * 25 / *(BYTE*)(ItemAttribute + 31) + 5;
			}
		}

        if (ExtOption)
        {
            *(BYTE*)(ObjectItem + 22) += 2 + (SetItemDropLevel / 60);
        }

        *(BYTE*)(ObjectItem + 22) += (min(9,Level)*3);

		switch ( Level-9 )
		{
		case 6: *(BYTE*)(ObjectItem + 22) += 9;	// +15
		case 5: *(BYTE*)(ObjectItem + 22) += 8;	// +14
		case 4: *(BYTE*)(ObjectItem + 22) += 7;	// +13
		case 3: *(BYTE*)(ObjectItem + 22) += 6;	// +12
		case 2: *(BYTE*)(ObjectItem + 22) += 5;	// +11
		case 1: *(BYTE*)(ObjectItem + 22) += 4;	// +10
		default: break;
		};
		
		*(BYTE*)(ObjectItem + 22) /= 2;

		if (*(WORD*)ObjectItem < GET_ITEM(2, 8) || *(WORD*)ObjectItem > GET_ITEM(2, 15))
		{
			*(BYTE*)(ObjectItem + 22) += Level * 2;
		}
	}

	if (*(BYTE *)(ItemAttribute + 38)) // -> SuccessfulBlocking
	{
		if (Excel > 0 && *(BYTE*)(ItemAttribute + 31))
		{
			*(BYTE*)(ObjectItem + 16) += *(BYTE *)(ItemAttribute + 38) * 25 / *(BYTE*)(ItemAttribute + 31) + 5;
		}

		*(BYTE*)(ObjectItem + 16) += (min(9, Level) * 3);

		switch (Level - 9)
		{
		case 6: *(BYTE*)(ObjectItem + 16) += 9;	// +15
		case 5: *(BYTE*)(ObjectItem + 16) += 8;	// +14
		case 4: *(BYTE*)(ObjectItem + 16) += 7;	// +13
		case 3: *(BYTE*)(ObjectItem + 16) += 6;	// +12
		case 2: *(BYTE*)(ObjectItem + 16) += 5;	// +11
		case 1: *(BYTE*)(ObjectItem + 16) += 4;	// +10
		default: break;
		};
	}

	if (*(BYTE*)(ItemAttribute + 39)) // -> Defense
	{
		if(*(WORD*)ObjectItem >= 3072 && *(WORD*)ObjectItem < 3584) // -> Rever esta parte
		{
     		*(WORD*)(ObjectItem + 18) += Level;

            if (ExtOption)
            {
                *(WORD*)(ObjectItem + 18) = *(WORD*)(ObjectItem + 18) + (*(WORD*)(ObjectItem + 18) * 20 / SetItemDropLevel + 2);
            }
		}
		else
		{
			if (Excel > 0 && *(BYTE*)(ItemAttribute + 31))
			{
      			*(WORD*)(ObjectItem + 18) += *(BYTE*)(ItemAttribute + 39) * 12 / *(BYTE*)(ItemAttribute + 31) + 4 + *(BYTE*)(ItemAttribute + 31) / 5;
			}

            if (ExtOption)
            {
                *(WORD*)(ObjectItem + 18) = *(WORD*)(ObjectItem + 18) + (*(WORD*)(ObjectItem + 18) * 3 / SetItemDropLevel + 2 + SetItemDropLevel / 30);
            }

			if (*(WORD*)ObjectItem >= GET_ITEM(12, 3) && *(WORD*)ObjectItem <= GET_ITEM(12, 6))
			{
				*(WORD*)(ObjectItem + 18) += (min(9, Level) * 2);
			}
			else if(*(WORD*)ObjectItem == GET_ITEM(13, 30))
			{
				*(WORD*)(ObjectItem + 18) += (min(9, Level) * 2);
			}
			else
            {
                *(WORD*)(ObjectItem + 18) += (min(9, Level) * 3);
            }

			switch (Level - 9)
			{
			case 6: *(WORD*)(ObjectItem + 18) += 9;	// +15
			case 5: *(WORD*)(ObjectItem + 18) += 8;	// +14
			case 4: *(WORD*)(ObjectItem + 18) += 7;	// +13
			case 3: *(WORD*)(ObjectItem + 18) += 6;	// +12
			case 2: *(WORD*)(ObjectItem + 18) += 5;	// +11
			case 1: *(WORD*)(ObjectItem + 18) += 4;	// +10
			default: break;
			};
		}
	}

	if (*(BYTE*)(ItemAttribute + 40)) // -> MagicDefense
	{
		*(WORD*)(ObjectItem + 20) += (min(9, Level) * 3);

		switch (Level - 9)
		{
		case 6: *(WORD*)(ObjectItem + 20) += 9;	// +15
		case 5: *(WORD*)(ObjectItem + 20) += 8;	// +14
		case 4: *(WORD*)(ObjectItem + 20) += 7;	// +13
		case 3: *(WORD*)(ObjectItem + 20) += 6;	// +12
		case 2: *(WORD*)(ObjectItem + 20) += 5;	// +11
		case 1: *(WORD*)(ObjectItem + 20) += 4;	// +10
		default: break;
		};
	}

	int ItemLevel = *(BYTE*)(ItemAttribute + 31);

	if (Excel)
	{
		ItemLevel = ItemLevel + 25;
	}
	else if(ExtOption)
	{
		ItemLevel = ItemLevel + 30;
	}

	int AddValue = 4;

	if (*(WORD*)ObjectItem >= GET_ITEM(12, 3) && *(WORD*)ObjectItem <= GET_ITEM(12, 6))
    {
        AddValue = 5;
    }

	if(*(WORD*)(ItemAttribute + 56) && ((*(WORD*)ObjectItem >= 0 && *(WORD*)ObjectItem < 6144) || *(WORD*)ObjectItem >= 6151 && *(WORD*)ObjectItem <= 6656))
	{
		*(WORD*)(ObjectItem + 40) = *(WORD*)(ItemAttribute + 56); // -> RequireLevel
	}
	else if(*(WORD*)(ItemAttribute + 56) && ((*(WORD*)ObjectItem >= GET_ITEM(12, 0) && *(WORD*)ObjectItem <= GET_ITEM(12, 7)) || *(WORD*)ObjectItem >= GET_ITEM(13, 0)))
	{
		*(WORD*)(ObjectItem + 40) = *(WORD*)(ItemAttribute + 56) + Level * AddValue;
	}
	else
	{
		*(WORD*)(ObjectItem + 40) = 0;
	}

	if (*(WORD*)(ItemAttribute + 46)) // -> RequireStrength
	{
		*(WORD*)(ObjectItem + 30) = 20 + (*(WORD*)(ItemAttribute + 46)) * (ItemLevel + Level * 3) * 3 / 100;
	}
	else
	{
		*(WORD*)(ObjectItem + 30) = 0;
	}

	if (*(WORD*)(ItemAttribute + 48)) // -> RequireDexterity
	{
		*(WORD*)(ObjectItem + 32) = 20 + (*(WORD*)(ItemAttribute + 48)) * (ItemLevel + Level * 3) * 3 / 100;
	}
	else
	{
		*(WORD*)(ObjectItem + 32) = 0;
	}

	if (*(WORD*)(ItemAttribute + 52)) // -> RequireVitality
	{
		*(WORD*)(ObjectItem + 36) = 20 + (*(WORD*)(ItemAttribute + 52)) * (ItemLevel + Level * 3) * 3 / 100;
	}
	else
	{
		*(WORD*)(ObjectItem + 36) = 0;
	}

	if (*(WORD*)(ItemAttribute + 50)) // -> RequireEnergy
	{
		*(WORD*)(ObjectItem + 34) = 20 + (*(WORD*)(ItemAttribute + 50)) * (ItemLevel + Level * 1) * 3 / 100;
	}
	else
	{
		*(WORD*)(ObjectItem + 34) = 0;
	}

	if (*(WORD*)(ItemAttribute + 54)) // -> RequireCharisma
	{
		*(WORD*)(ObjectItem + 38) = 20 + (*(WORD*)(ItemAttribute + 54)) * (ItemLevel + Level * 3) * 3 / 100;
	}
	else
	{
		*(WORD*)(ObjectItem + 38) = 0;
	}

	if(*(WORD*)ObjectItem == GET_ITEM(12, 11))
    {
        WORD Energy;

        switch(Level)
        {
		case 0: Energy = 30;	break;
		case 1: Energy = 60;	break;
		case 2: Energy = 90;	break;
		case 3: Energy = 130;	break;
		case 4: Energy = 170;	break;
		case 5: Energy = 210;	break;
		case 6: Energy = 300;	break;
        }

        *(WORD*)(ObjectItem + 34) = Energy;
    }

	if (*(WORD*)(ItemAttribute + 54)) // -> RequireCharisma
    {
        if (*(WORD*)ObjectItem == 7176)
            *(WORD*)(ObjectItem + 38) = (185+(*(WORD*)(ItemAttribute + 54)*15));
        else
            *(WORD*)(ObjectItem + 38) = *(WORD*)(ItemAttribute + 54);
    }

	if (*(WORD*)ObjectItem == GET_ITEM(13, 10))
	{
		if ( Level <= 2 )
			*(WORD*)(ObjectItem + 40) = 20;
		else
			*(WORD*)(ObjectItem + 40) = 50;
	}

	if( (*(WORD*)ObjectItem >= GET_ITEM(7,29) && *(WORD*)ObjectItem <= GET_ITEM(7,33)) ||
		(*(WORD*)ObjectItem >= GET_ITEM(8,29) && *(WORD*)ObjectItem <= GET_ITEM(8,33)) ||
		(*(WORD*)ObjectItem >= GET_ITEM(9,29) && *(WORD*)ObjectItem <= GET_ITEM(9,33)) ||
		(*(WORD*)ObjectItem >= GET_ITEM(10,29) && *(WORD*)ObjectItem <= GET_ITEM(10,33)) ||
		(*(WORD*)ObjectItem >= GET_ITEM(11,29) && *(WORD*)ObjectItem <= GET_ITEM(11,33))  ||
		*(WORD*)ObjectItem == GET_ITEM(0,22) ||
		*(WORD*)ObjectItem == GET_ITEM(0,23) ||
		*(WORD*)ObjectItem == GET_ITEM(5,12) ||
		*(WORD*)ObjectItem == GET_ITEM(4,21) ||
		*(WORD*)ObjectItem == GET_ITEM(2,14))
	{
		Excel = 0;
	}

	if (Excel > 0)
	{
		if(*(WORD*)(ObjectItem + 40) > 0) // -> RequireLevel
		{
      		*(WORD*)(ObjectItem + 40) += 20;
		}
	}

	*(BYTE*)(ObjectItem + 42) = 0; // -> Special Num

	if (*(WORD*)ObjectItem >= GET_ITEM(12,3) && *(WORD*)ObjectItem <= GET_ITEM(12,512))
	{
		if (Attribute2 & 0x01)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 50 + Level * 5;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 100; // -> Improve HP Max
			++*(BYTE*)(ObjectItem + 42);
		}

		if (Attribute2 & 0x02)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 50 + Level * 5;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 101; // -> Improve MP Max
			++*(BYTE*)(ObjectItem + 42);
        }

        if (Attribute2 & 0x04)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 3;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 102; // -> One Percent Damage
			++*(BYTE*)(ObjectItem + 42);
        }
        
        if (Attribute2 & 0x08)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 50;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 103; // -> Improve AG Max
			++*(BYTE*)(ObjectItem + 42);
        }

        if (Attribute2 & 0x10)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 5;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 97;
			++*(BYTE*)(ObjectItem + 42);
        }
	}
	else if (*(WORD*)ObjectItem == GET_ITEM(13,30)) 
	{
		int Cal = 0;

		if(Level <= 9)
		{
			Cal = Level;
		}
		else
		{
			Cal = 9;
		}

		*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 15 + Cal * 2;

		switch(Level - 9)
		{
		case 6: *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) += 9;	// +15
		case 5: *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) += 8;	// +14
		case 4: *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) += 7;	// +13
		case 3: *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) += 6;	// +12
		case 2: *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) += 5;	// +11
		case 1: *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) += 4;	// +10
		default: break;
		};

		*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 150; // -> Set Option Improve Defence
		++*(BYTE*)(ObjectItem + 42);

		*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 20 + Level * 2;
		*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 148; // -> Set Option Improve Damage
		++*(BYTE*)(ObjectItem + 42);

		if (Attribute2 & 0x01)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 50 + Level * 5;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 100; // -> Improve HP Max
			++*(BYTE*)(ObjectItem + 42);
        }
        
        if (Attribute2 & 0x02)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 50 + Level * 5;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 101; // -> Improve MP Max
			++*(BYTE*)(ObjectItem + 42);
        }
        
        if (Attribute2 & 0x04)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 3;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 102; // -> One Percent Damage
			++*(BYTE*)(ObjectItem + 42);
        }
        
        if (Attribute2 & 0x08)
        {
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 10 + Level * 5;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 144;  // -> Set Option Improve Charisma
			++*(BYTE*)(ObjectItem + 42);
        }
	}

	if (Attribute1 & 0x80)
	{
		if (*(BYTE*)(ItemAttribute + 33)) // -> SkillIndex
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = *(BYTE*)(ItemAttribute + 33);
			++*(BYTE*)(ObjectItem + 42);
		}
	}

	if (Attribute1 & 0x04)
	{
		if (*(WORD*)ObjectItem >= GET_ITEM(0, 0) && *(WORD*)ObjectItem < 6144)
		{
			if(*(WORD*)ObjectItem != GET_ITEM(4, 7) && *(WORD*)ObjectItem != GET_ITEM(4, 15))
			{
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 84; // -> Luck
				++*(BYTE*)(ObjectItem + 42);
			}
		}

		if (*(WORD*)ObjectItem >= GET_ITEM(12, 0) && *(WORD*)ObjectItem <= GET_ITEM(12, 300))
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 84; // -> Luck
			++*(BYTE*)(ObjectItem + 42);
		}

		if (*(WORD*)ObjectItem >= GET_ITEM(13, 30))
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 84; // -> Luck
			++*(BYTE*)(ObjectItem + 42);
		}
	}

	int Option3 = (Attribute1 & 3) + 4 * ((Attribute2 >> 6) & 1);

	if (Option3)
	{
		if (*(WORD*)ObjectItem == GET_ITEM(13, 3))
        {
			if (Option3 & 0x01)
            {
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 5;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 104; // -> Damage Absorb (Verificar)
				++*(BYTE*)(ObjectItem + 42);
            }

            if (Option3 & 0x02)
            {
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 50;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 103; // -> Improve AG Max (Verificar)
				++*(BYTE*)(ObjectItem + 42);
            }

            if (Option3 & 0x04)
            {
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 5;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 97; // -> Improve Attack Speed (Verificar)
				++*(BYTE*)(ObjectItem + 42);
            }
		}
		else
		{
			if (*(WORD*)ObjectItem >= GET_ITEM(0,0) && *(WORD*)ObjectItem < GET_ITEM(5,0))
		    {
			    if (*(WORD*)ObjectItem != GET_ITEM(4,7) && *(WORD*)ObjectItem != GET_ITEM(4,15))
			    {
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 80; // -> Improve Damage
					++*(BYTE*)(ObjectItem + 42);
					*(WORD*)(ObjectItem + 30) += Option3 * 5;
			    }
		    }

			if (*(WORD*)ObjectItem >= GET_ITEM(5,0) && *(WORD*)ObjectItem < GET_ITEM(6,0))
		    {
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 81; // -> Improve Magic
				++*(BYTE*)(ObjectItem + 42);
				*(WORD*)(ObjectItem + 30) += Option3 * 5;
		    }

			if (*(WORD*)ObjectItem >= GET_ITEM(6,0) && *(WORD*)ObjectItem < GET_ITEM(7,0))
		    {
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 5;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 82; // -> Improve Blocking
				++*(BYTE*)(ObjectItem + 42);
				*(WORD*)(ObjectItem + 30) += Option3 * 5;
		    }

			if (*(WORD*)ObjectItem >= GET_ITEM(7,0) && *(WORD*)ObjectItem < GET_ITEM(12, 0))
		    {
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 83; // -> Improve Defense
				++*(BYTE*)(ObjectItem + 42);
				*(WORD*)(ObjectItem + 30) += Option3 * 5;
		    }

			if (*(WORD*)ObjectItem >= GET_ITEM(13,8) && *(WORD*)ObjectItem < GET_ITEM(14,0) && *(WORD*)ObjectItem != GET_ITEM(13,30))
		    {
                if (*(WORD*)ObjectItem == GET_ITEM(13,24))
                {
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 175; // -> Improve Max Mana (Verificar)
					++*(BYTE*)(ObjectItem + 42);
                }
                else if (*(WORD*)ObjectItem == GET_ITEM(13,28))
                {
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 176; //-> Improve Max AG (Verificar)
					++*(BYTE*)(ObjectItem + 42);
                }
                else
                {
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 85; // -> Life Regeneration
					++*(BYTE*)(ObjectItem + 42);
                }
            }

			if (*(WORD*)ObjectItem == GET_ITEM(12,0))
		    {
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 85; // -> Life Regeneration
				++*(BYTE*)(ObjectItem + 42);
		    }
			else if (*(WORD*)ObjectItem == GET_ITEM(12,1))
			{
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 81; // -> Improve Magic
				++*(BYTE*)(ObjectItem + 42);
			}
			else if (*(WORD*)ObjectItem == GET_ITEM(12,2))
			{
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 80; // -> Improve Damage
				++*(BYTE*)(ObjectItem + 42);
			}
			else if (*(WORD*)ObjectItem == GET_ITEM(12,3))
            {
				if (Attribute2 & 0x20)
                {
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 85; // -> Life Regeneration
					++*(BYTE*)(ObjectItem + 42);
                }
                else
                {
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 80; // -> Improve Damage
					++*(BYTE*)(ObjectItem + 42);
                }
            }
			else if (*(WORD*)ObjectItem == GET_ITEM(12,4))
            {
                if (Attribute2 & 0x20)
                {
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
					*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 81; // -> Improve Magic
					++*(BYTE*)(ObjectItem + 42);
                }
                else
                {
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 85; // -> Life Regeneration
					++*(BYTE*)(ObjectItem + 42);
                }
            }
			else if (*(WORD*)ObjectItem == GET_ITEM(12,5) || *(WORD*)ObjectItem >= GET_ITEM(12,36) && *(WORD*)ObjectItem <= GET_ITEM(12,511))
            {
                if (Attribute2 & 0x20)
                {
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 80; // -> Improve Damage
					++*(BYTE*)(ObjectItem + 42);
                }
                else
                {
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3;
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 85; // -> Life Regeneration
					++*(BYTE*)(ObjectItem + 42);
                }
            }
			else if (*(WORD*)ObjectItem == GET_ITEM(12,512))
            {
                if (Attribute2 & 0x20)
                {
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 80; // -> Improve Damage
					++*(BYTE*)(ObjectItem + 42);
                }
                else
                {
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
			        *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 81; // -> Improve Magic
					++*(BYTE*)(ObjectItem + 42);
                }
            }
			else if (*(WORD*)ObjectItem == GET_ITEM(13,30))
		    {
			    *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = Option3 * 4;
			    *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 80; // -> Improve Damage
				++*(BYTE*)(ObjectItem + 42);
		    }
		}
	}

	if (*(WORD*)ObjectItem == GET_ITEM(13,4))
    {
		pPetItemConvert(ObjectItem);
	}

	if ((*(WORD*)ObjectItem >= GET_ITEM(6,0) && *(WORD*)ObjectItem < GET_ITEM(12,0)) || (*(WORD*)ObjectItem >= GET_ITEM(13,8) && *(WORD*)ObjectItem <= GET_ITEM(13,9))
       || (*(WORD*)ObjectItem >= GET_ITEM(13,21) && *(WORD*)ObjectItem <= GET_ITEM(13,24)))
	{
		if (Attribute2 & 0x20)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 86; // -> Improve Life
			++*(BYTE*)(ObjectItem + 42);
		}	
		
		if (Attribute2 & 0x10)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 87; // -> Improve Mana
			++*(BYTE*)(ObjectItem + 42);
		}	

		if (Attribute2 & 0x8)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 88; // -> Decrease Damage
			++*(BYTE*)(ObjectItem + 42);
		}	

		if (Attribute2 & 0x4)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 89; // -> Reflection Damage
			++*(BYTE*)(ObjectItem + 42);
		}	
		
		if (Attribute2 & 0x2)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 90; // -> Improve Blocking Percent
			++*(BYTE*)(ObjectItem + 42);
		}	

		if (Attribute2 & 0x1)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 91; // -> Improve Gain Gold
			++*(BYTE*)(ObjectItem + 42);
		}	
	}

	if ((*(WORD*)ObjectItem >= GET_ITEM(0,0) && *(WORD*)ObjectItem < GET_ITEM(6,0)) ||
       (*(WORD*)ObjectItem >= GET_ITEM(13,12) && *(WORD*)ObjectItem <= GET_ITEM(13,13))
       || (*(WORD*)ObjectItem >= GET_ITEM(13,25) && *(WORD*)ObjectItem <= GET_ITEM(13,28)))
	{
		if (Attribute2 & 0x20)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 92; // Excellent Damage
			++*(BYTE*)(ObjectItem + 42);
		}	

		if ((*(WORD*)ObjectItem >= GET_ITEM(5,0) && *(WORD*)ObjectItem < GET_ITEM(6,0)) || (*(WORD*)ObjectItem == GET_ITEM(13,12))
           || (*(WORD*)ObjectItem == GET_ITEM(13,25) || *(WORD*)ObjectItem == GET_ITEM(13,27)))
		{
			if (Attribute2 & 0x10)
			{
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = gUser.m_ItemStat.Level / 20;
			    *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 95; // -> Improve Magic Level
				++*(BYTE*)(ObjectItem + 42);
			}	
			
			if (Attribute2 & 0x8)
			{
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 2;
			    *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 96; // -> Improve Magic Percent
				++*(BYTE*)(ObjectItem + 42);
			}	
		}
		else
		{
			if (Attribute2 & 0x10)
			{
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = gUser.m_ItemStat.Level  / 20;
			    *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 93; // -> Improve Damage Level
				++*(BYTE*)(ObjectItem + 42);
			}	

			if (Attribute2 & 0x8)
			{
				*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 2;
			    *(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 94; // -> Improve Damage Percent
				++*(BYTE*)(ObjectItem + 42);
			}	
		}

		if (Attribute2 & 4)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 7;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 97; // AT_IMPROVE_ATTACK_SPEED
			++*(BYTE*)(ObjectItem + 42);
		}	

		if (Attribute2 & 2)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 98; // AT_IMPROVE_GAIN_LIFE
			++*(BYTE*)(ObjectItem + 42);
		}	

		if (Attribute2 & 1)
		{
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 99; // AT_IMPROVE_GAIN_MANA
			++*(BYTE*)(ObjectItem + 42);
		}	
	}

	if (*(WORD*)ObjectItem == GET_ITEM(13,20))
	{
        switch (Level)
        {
        case 0:
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 10;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 96; // AT_IMPROVE_MAGIC_PERCENT
			++*(BYTE*)(ObjectItem + 42);

			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 10;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 94; // AT_IMPROVE_DAMAGE_PERCENT
			++*(BYTE*)(ObjectItem + 42);

			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 10;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 97; // AT_IMPROVE_ATTACK_SPEED
			++*(BYTE*)(ObjectItem + 42);
            break;

        case 3:
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 10;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 96; // AT_IMPROVE_MAGIC_PERCENT
			++*(BYTE*)(ObjectItem + 42);

			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 10;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 94; // AT_IMPROVE_DAMAGE_PERCENT
			++*(BYTE*)(ObjectItem + 42);

			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 51) = 10;
			*(BYTE*)(*(BYTE*)(ObjectItem + 42) + ObjectItem + 43) = 97; // AT_IMPROVE_ATTACK_SPEED
			++*(BYTE*)(ObjectItem + 42);
            break;
        }
	}

	if (*(WORD*)ObjectItem>= GET_ITEM(4,0) && *(WORD*)ObjectItem < GET_ITEM(4,8))
	{
		*(BYTE*)(ObjectItem + 8) = 1; // EQUIPMENT_WEAPON_LEFT
	}
	else if (*(WORD*)ObjectItem >= GET_ITEM(0,0) && *(WORD*)ObjectItem < GET_ITEM(6,0))
	{
		*(BYTE*)(ObjectItem + 8) = 0; // EQUIPMENT_WEAPON_RIGHT
	}
	else if (*(WORD*)ObjectItem >= GET_ITEM(6,0) && *(WORD*)ObjectItem < GET_ITEM(7,0))
	{
		*(BYTE*)(ObjectItem + 8) = 1; // EQUIPMENT_WEAPON_LEFT
	}
	else if (*(WORD*)ObjectItem >= GET_ITEM(7,0) && *(WORD*)ObjectItem < GET_ITEM(8,0))
	{
		*(BYTE*)(ObjectItem + 8) = 2; // EQUIPMENT_HELM
	}
	else if(*(WORD*)ObjectItem >= GET_ITEM(8,0) && *(WORD*)ObjectItem < GET_ITEM(9,0))
		*(BYTE*)(ObjectItem + 8) = 3; // EQUIPMENT_ARMOR
	else if(*(WORD*)ObjectItem >= GET_ITEM(9,0) && *(WORD*)ObjectItem < GET_ITEM(10,0))
		*(BYTE*)(ObjectItem + 8) = 4; // EQUIPMENT_PANTS
	else if(*(WORD*)ObjectItem >= GET_ITEM(10,0) && *(WORD*)ObjectItem < GET_ITEM(11,0))
		*(BYTE*)(ObjectItem + 8) = 5; // EQUIPMENT_GLOVES
	else if(*(WORD*)ObjectItem >= GET_ITEM(11,0) && *(WORD*)ObjectItem < GET_ITEM(12,0))
		*(BYTE*)(ObjectItem + 8) = 6; // EQUIPMENT_BOOTS
	else if(*(WORD*)ObjectItem >= GET_ITEM(12,0) && *(WORD*)ObjectItem < GET_ITEM(12,7))
		*(BYTE*)(ObjectItem + 8) = 7; // EQUIPMENT_WING
	else if(*(WORD*)ObjectItem == GET_ITEM(13,5))
		*(BYTE*)(ObjectItem + 8) = 1; // EQUIPMENT_WEAPON_LEFT
	else if(*(WORD*)ObjectItem >= GET_ITEM(13,0) && *(WORD*)ObjectItem < GET_ITEM(13,8))
		*(BYTE*)(ObjectItem + 8) = 8; // EQUIPMENT_HELPER
    else if((*(WORD*)ObjectItem >= GET_ITEM(13,8) && *(WORD*)ObjectItem < GET_ITEM(13,12)) || (*(WORD*)ObjectItem == GET_ITEM(13,20) && Level == 0) || (*(WORD*)ObjectItem == GET_ITEM(13,20) && Level == 3))
		*(BYTE*)(ObjectItem + 8) = 10; // EQUIPMENT_RING_RIGHT
    else if(*(WORD*)ObjectItem >= GET_ITEM(13,21) && *(WORD*)ObjectItem <= GET_ITEM(13,24))
		*(BYTE*)(ObjectItem + 8) = 10; // EQUIPMENT_RING_RIGHT
    else if( *(WORD*)ObjectItem >= GET_ITEM(13,25) && *(WORD*)ObjectItem <= GET_ITEM(13,28))
		*(BYTE*)(ObjectItem + 8) = 9; // EQUIPMENT_AMULET
	else if(*(WORD*)ObjectItem >= GET_ITEM(13,12) && *(WORD*)ObjectItem < GET_ITEM(14,0))
		*(BYTE*)(ObjectItem + 8) = 9; // EQUIPMENT_AMULET
	else 
		*(BYTE*)(ObjectItem + 8) = -1;
}