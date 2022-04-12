#pragma once
// ----------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------

#define	MAX_XOR_KEYS		32
#define MAX_CHECK_VARS		10
#define MAX_STAT_LIMIT		300
#define MAX_SPEED_LIMIT		100
#define MAX_FRAME_VALUE		40
// ----------------------------------------------------------------------------------------------

enum eCheckStatMember
{
	emLevel = 0,
	emLevelPoint = 1,
	emStrength = 2,
	emDexterity = 3,
	emVitality = 4,
	emEnergy = 5,
	emLeadership = 6,
	emAttackSpeed = 7,
	emMagicSpeed = 8,
	emFrameValue = 9,
};
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)

#pragma pack(pop)
// ----------------------------------------------------------------------------------------------



class CheatGuard
{
public:
	void	Load();
	// ----
	void	ChangeXORFilter();
	bool	IsCorrectFrame();
	int		GetLargerFrame();
	// ----
	unsigned char	XOR[MAX_XOR_KEYS];
	// ----
}; extern CheatGuard gCheatGuard;
// ----------------------------------------------------------------------------------------------