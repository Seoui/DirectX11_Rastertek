#ifndef _TEXTURECLASS_H_
#define _TEXTURECLASS_H_

// INCLUDES
#include <d3d11.h>
#include "DirectXTex.h"

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