#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_

// INCLUDES
#include <d3d11.h>
#include "DirectXTex.h"

// ShaderResourceView를 만드는 클래스
// 그냥 텍스처를 의미하는 클래스라고 생각해도 됨
class TextureClass
{
public:
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D11Device*, const WCHAR*);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* mTextureView;
};
#endif