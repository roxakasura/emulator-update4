#pragma once

#define pLoadImage				((void(*)(char * Folder, int ImageID, int BlendType, int a4, int a5, int a6)) 0x0062C1E0)
#define pLoadImageTga			((void(*)(char * Folder, int ImageID, int BlendType, int a4, int a5, int a6)) 0x0062C670)
#define pSetBlend				((void(__cdecl*)(BYTE Mode)) 0x60CB90)

class Interface
{
public:
	//Interface();


	void		Load();
	static void	Work();
	void		LoadImage(int Type, char * Folder, int ImageID);
	
private:
	
};

extern Interface gInterface;
