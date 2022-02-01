/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXInputLayout.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Input Layout
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twInputLayout.h"

//--------------------------------------------------------------------------------------
// DIRECTX INPUT LAYOUT CLASS
//--------------------------------------------------------------------------------------
class twDXInputLayout : public twInputLayout
{
private:
	ID3D11InputLayout* m_ptrInputLayout;

	friend class twAPIManager;

public:
	twDXInputLayout() = default;
	~twDXInputLayout()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrInputLayout);
	}
};

