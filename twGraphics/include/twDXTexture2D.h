/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXTexture2D.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Texture 2D
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twTexture2D.h"

//--------------------------------------------------------------------------------------
// DIRECTX TEXTURE 2D CLASS
//--------------------------------------------------------------------------------------
class twDXTexture2D : public twTexture2D
{
private:
	ID3D11Texture2D* m_ptrTexture;

	friend class twAPIManager;

public:
	twDXTexture2D() = default;
	~twDXTexture2D()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrTexture);
	}
};

