/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXDepthStencil.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX DepthStencil
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twDepthStencilView.h"

//--------------------------------------------------------------------------------------
// DIRECTX DEPTH STENCIL CLASS
//--------------------------------------------------------------------------------------
class twDXDepthStencilView : public twDepthStencilView
{
private:
	ID3D11DepthStencilView* m_ptrDepthStencilView;

	friend class twAPIManager;

public:
	twDXDepthStencilView() = default;
	~twDXDepthStencilView()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrDepthStencilView);
	}
};

