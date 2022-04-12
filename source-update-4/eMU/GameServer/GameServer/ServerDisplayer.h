// ServerDisplayer.h: interface for the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_LOG_TEXT_LINE 29
#define MAX_LOG_TEXT_SIZE 80

enum eLogColor
{
	LOG_BLACK = 0,
	LOG_RED = 1,
	LOG_GREEN = 2,
	LOG_BLUE = 3,
};

struct LOG_DISPLAY_INFO
{
	char text[MAX_LOG_TEXT_SIZE];
	eLogColor color;
};

class CServerDisplayer
{
public:
	CServerDisplayer();
	virtual ~CServerDisplayer();
	void Init(HWND hWnd);
	void Run();
	void SetWindowName();
	void PaintAllInfo();
	void LogTextPaint();
	void LogAddText(eLogColor color,char* text,int size);
	int EventBc;
	int EventDs;
	int EventCc;
	int EventIt;	
	int EventInvasion[30];
private:
	HWND m_hwnd;
	HFONT m_font;
	HFONT m_font3;
	HBRUSH m_brush[2];
	LOG_DISPLAY_INFO m_log[MAX_LOG_TEXT_LINE];
	int m_count;
	char m_DisplayerText[2][64];
};

extern CServerDisplayer gServerDisplayer;
