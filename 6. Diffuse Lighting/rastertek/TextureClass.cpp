#include "TextureClass.h"
using namespace DirectX;

TextureClass::TextureClass()
{
	mTextureView = 0;
}

TextureClass::TextureClass(const TextureClass &)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D11Device * device, const WCHAR * fileName)
{
	HRESULT result;
	ScratchImage image;
	WCHAR ext[4];
	size_t l = wcslen(fileName);
	wcsncpy_s(ext, &fileName[l - 3], 3);
	ext[3] = '\0';
	if (wcscmp(ext, L"tga") == 0)
	{
		result = LoadFromTGAFile(fileName, nullptr, image);
	}
	else if (wcscmp(ext, L"dds") == 0)
	{
		result = LoadFromDDSFile(fileName, DDS_FLAGS_NONE, nullptr, image);
	}
	else if (wcscmp(ext, L"jpg") == 0 || wcscmp(ext, L"png") == 0)
	{
		result = LoadFromWICFile(fileName, WIC_FLAGS_NONE, nullptr, image);
	}
	if (FAILED(result)) return false;


	result = CreateShaderResourceView(device, image.GetImages(),
		image.GetImageCount(), image.GetMetadata(), &mTextureView);
	if (FAILED(result)) return false;

	return true;
}

void TextureClass::Shutdown()
{
	// Release the texture resource.
	if (mTextureView)
	{
		mTextureView->Release();
		mTextureView = 0;
	}

	return;
}

ID3D11ShaderResourceView * TextureClass::GetTexture()
{
	return mTextureView;
}