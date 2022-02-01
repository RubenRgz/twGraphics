/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXRenderTargetView.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Render Target View
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twRenderTargetView.h"

//--------------------------------------------------------------------------------------
// DIRECTX RENDER TARGET VIEW CLASS
//--------------------------------------------------------------------------------------
class twDXRenderTargetView : public twRenderTargetView
{
private:
	ID3D11RenderTargetView* m_ptrRenderTargetView;

	friend class twAPIManager;

public:
	twDXRenderTargetView() = default;
	~twDXRenderTargetView()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrRenderTargetView);
	}
};

