/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twSamplerState.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Sampler State class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// SAMPLER STATE CLASS
//--------------------------------------------------------------------------------------
class twSamplerState
{
public:
	twSamplerState() = default;
	virtual ~twSamplerState() {};

	virtual void Destroy() = 0;
};