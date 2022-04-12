#pragma once
#define iDraw_ToolTip			0x0053DEB0 // 1.04j
#define iDraw_Interface			0x0059F330 // 1.04j
#define oDrawInterface_Call		0x0059D3F3 // 1.04j OK
#define pSetCursorFocus			*(DWORD*)0x7B02758
#define MIN_WIN_WIDTH			640
#define MIN_WIN_HEIGHT			480
#define MAX_OBJECT				250

enum ObjWindow // -> Season 3.1
{
	FriendList					= 1,
	MoveList					= 2,
	Party						= 3,
	Quest						= 4,
	Guild						= 5, 
	Trade						= 6, 
	Warehouse					= 7, 
	ChaosBox					= 9, 
	CommandWindow				= 10,
	DevilSquare					= 13,
	DividedServer				= 14,
	BloodCastle					= 15,
	Trainer						= 16,
	Shop						= 17,
	PersonalShop				= 18,
	CreateGuild					= 19,
	NpcGuardSiege				= 20,
	SeniorNPC					= 21,
	BlackWindow					= 22,
	CatapultNPCSiegeAttack		= 23,
	CatapultNPCSiegeDefense		= 24,
	CastleGateSwitch			= 25,
	InfoCharacter				= 26,
	Inventory					= 27,
	ReforceItem					= 28,
	Elpis						= 29,
	KanturuEntrace				= 30,
	BarracksEntrace				= 31,
	IllusionEntrace				= 32,
	HeroList					= 34,
};

struct InterfaceObject
{
	DWORD	ModelID;
	float	Width;
	float	Height;
	float	X;
	float	Y;
	float	MaxX;
	float	MaxY;
	DWORD	EventTick;
	bool	OnClick;
	bool	OnShow;
	BYTE	Attribute;
	bool	ByClose;
	long	OpenedValue;
	BYTE	Speed;
	char	StatValue[20];
	int		Type;
	//
	bool	FirstLoad;
	void Close()
	{
		this->OnShow = false;
		pSetCursorFocus = false;
		this->ByClose = false;
	};

	void Open()
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->ByClose = false;
	};

	void Open(int Value, int Speed)
	{
		this->OnShow = true; pSetCursorFocus = true;
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
		this->FirstLoad = true;
	};

		void Close(int Value, int Speed)
	{
		this->OnShow = false; pSetCursorFocus = false; 
		this->OpenedValue = Value;
		this->Speed = Speed;
		this->ByClose = false;
	}

	void CloseAnimated(int Speed)
	{
		pSetCursorFocus = false;
		this->Speed = Speed;
		this->ByClose = true;
	}


};

int TestandoItemDraw(int a1, int a2, int a3, int a4, int a5, int a6, char a7);

#define pDrawItemModelFull			((int(__cdecl*)(int a1, int a2, int a3, int a4, GLfloat alpha, int a6, int a7, int a8, int a9, char a10, char a11, int a12, int a13)) 0x628611) //1.04j
#define pDrawItemModel				((int(__cdecl*)(int ItemID, int a2, int a3, int a4, int a5, int a6, char a7)) 0x5E7110) //1.04j
#define pDrawButton					((void(__cdecl*)(DWORD, float, float, float, float, float, float)) 0x006E27D3)
#define pLoadImageJPG				((void(cdecl*)(char *Folder, int ModelID, int a3, int a4, int a5, int a6)) 0x006F9D4F)
#define pLoadImageTGA				((void(cdecl*)(char *Folder, int ModelID, int a3, int a4, int a5, int a6)) 0x006FA244)
#define pDrawGUI					((void(__cdecl*)(int ObjectId, float X, float Y, float Width, float Height, int Arg6, int Arg7, float Width2, float Height2, char Arg10, float Arg11)) 0x6438B4)
//void WindowCustom();
class Interface
{
public:
	//Interface();


		   void	Load();
	static void	Work();
	static void DebugFuction();
	static void LoadImagem(int Type, char * Folder, int ImageID);
	static void DrawGUI(int ObjectId, float X, float Y, float Width, float Height, float ScaleX, float ScaleY);
		   bool IsWorkZone(short ObjectID);
		   void DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY);
		   void SetCursorFocus(int state);


		   bool boolVar; //Aquí variabel on,off
	InterfaceObject Data[MAX_OBJECT]; 
	DWORD timeboolVar;
	
private:
	
};
extern Interface gInterface;
extern int JanelaTeste;