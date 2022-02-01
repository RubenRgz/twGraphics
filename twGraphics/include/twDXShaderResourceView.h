/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXShaderResourceView.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Shader Resource View
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twShaderResourceView.h"

//--------------------------------------------------------------------------------------
//	DIRECTX SHADER RESOURCE VIEW CLASS
//--------------------------------------------------------------------------------------
class twDXShaderResourceView : public twShaderResourceView
{
private:
	ID3D11ShaderResourceView* m_ptrShaderResourceView;

	friend class twAPIManager;

public:
	twDXShaderResourceView() = default;
	~twDXShaderResourceView()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrShaderResourceView);
	}
};

