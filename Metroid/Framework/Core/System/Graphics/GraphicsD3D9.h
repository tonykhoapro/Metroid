#pragma once
#include "Core\System\System.h"
#include "Core\Interface\IGraphics.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <map>


class SystemManager;
struct Drawable;

class GraphicsD3D9 final : public System, public IGraphics
{
public:
	GraphicsD3D9() {};
	~GraphicsD3D9() {};
public:
	bool Initialize();
	void Update();
	bool Shutdown();
public:
	bool CreateTextureFromFile(const std::string& fileName, const ARGB& colorKey, int textureID);
	void RemoveTexture(int textureID);
	void GetImageInfoFromFile(const std::string& fileName, int& width, int& height);
	void AddToDrawQueue(const Transform& transform, int textureID, const Rect& rect, float pixelsPerUnit, int sortingOrder);
protected:
	inline void RenderBegin();
	inline void RenderDrawQueue();
	inline void Draw(const Transform& transform, int textureID, const Rect& rect, float pixelsPerUnit);
	inline void RenderEnd();
	inline void ClearDrawQueue();
public:
	void SetViewPosition(const Vec2& position);
	void SetViewSize(const Vec2& viewSize);
	void SetViewport(unsigned long x, unsigned long y, unsigned long width, unsigned long height, float MinZ, float MaxZ);// khong quan trong lam cho game 2D
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	HWND hWnd;
	LPD3DXSPRITE D3DSprite;

	int BackBufferWidth;
	int BackBufferHeight;

	std::list<Drawable*> DrawQueue;
	std::map<int, LPDIRECT3DTEXTURE9> TextureIDMap;
private:
	friend class SystemManager;
};

