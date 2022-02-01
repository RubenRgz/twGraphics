/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXSamplerState.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Sampler State
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twSamplerState.h"

//--------------------------------------------------------------------------------------
// DIRECTX SAMPLER STATE CLASS
//--------------------------------------------------------------------------------------
class twDXSamplerState : public twSamplerState
{
private:
	ID3D11SamplerState* m_ptrSamplerState;

	friend class twAPIManager;

public:
	twDXSamplerState() = default;
	~twDXSamplerState()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrSamplerState);
	}
};

