#ifndef _TOOLKIT_H
#define _TOOLKIT_H
// ---
enum ASM
{
	JMP	       = 0xE9,
	JE	       = 0x74,
	JNE        = 0x75,
	JGE        = 0x7D,
	NOP	       = 0x90,
	CALL       = 0xE8,
	EAX        = 0x50,
};
// ---
class CToolKit
{
public:
	void HookThis(DWORD dwMyFuncOffset, DWORD dwJmpOffset);
	// ---
	DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
	DWORD SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
	DWORD SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
	DWORD SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
	DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, BYTE cmd);
	DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue);
	DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd);
	DWORD SetByte(const LPVOID dwOffset, const BYTE btValue);
	DWORD SetFloat(const LPVOID dwOffset, float fValue);
	DWORD SetDouble(const LPVOID dwOffset, double dValue);
	DWORD SetDword(const LPVOID dwOffset, const DWORD dwValue);
	
	void SetCompleteHook(BYTE head,DWORD offset,...);
	// ---
	int Registry(const char* Section);
	void SendMsg(int ColorId, char * szMsg);
	void WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset);
	void SetByteP(DWORD dwSrcOffset, BYTE bOpCode);
};
extern CToolKit gToolKit;
// ---
#endif