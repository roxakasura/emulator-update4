class DOSConsole
{
public:
	int Write(char* Format, BOOL ShowHour, int Color);
	int StdIn(char* Buffer);
	void ChatCore(char* Input);
	void Init();
	void SetName();
	HANDLE Handle(BOOL Input);

	//Vars
	int SpyChat;
	int Log;
	int Enabled;
private:
};

extern DOSConsole Console;
