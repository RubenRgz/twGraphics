/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twRenderTargetView.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Render Target View class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// RENDER TARGET VIEW CLASS
//--------------------------------------------------------------------------------------
class twRenderTargetView
{
public:
	twRenderTargetView() = default;
	virtual ~twRenderTargetView() {};

	virtual void Destroy() = 0;
};
