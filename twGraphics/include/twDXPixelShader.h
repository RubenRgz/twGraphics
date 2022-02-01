/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXPixelShader.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Pixel Shader
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twPixelShader.h"

//--------------------------------------------------------------------------------------
// DIRECTX PIXEL SHADER CLASS
//--------------------------------------------------------------------------------------
class twDXPixelShader : public twPixelShader
{
private:
	ID3D11PixelShader* m_ptrPixelShader;

	friend class twAPIManager;

public:
	twDXPixelShader() = default;
	~twDXPixelShader()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrPixelShader);
	}
};

