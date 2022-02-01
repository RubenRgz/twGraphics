/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twDepthStencil.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Depth Stencil class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// DEPTH STENCIL CLASS
//--------------------------------------------------------------------------------------
class twDepthStencilView
{
public:
	twDepthStencilView() = default;
	virtual ~twDepthStencilView() {};

	virtual void Destroy() = 0;
};