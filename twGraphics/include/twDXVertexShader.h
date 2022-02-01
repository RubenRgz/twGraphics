/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXVertexShader.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Vertex Shader
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twVertexShader.h"

//--------------------------------------------------------------------------------------
// DIRECTX VERTEX SHADER CLASS
//--------------------------------------------------------------------------------------
class twDXVertexShader : public twVertexShader
{
private:
	ID3D11VertexShader* m_ptrVertexShader;

	friend class twAPIManager;

public:
	twDXVertexShader() = default;
	~twDXVertexShader() 
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrVertexShader);
	}
};

