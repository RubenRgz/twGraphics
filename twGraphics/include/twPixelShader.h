/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twPixelShader.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Pixel Shader class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// PIXEL SHADER CLASS
//--------------------------------------------------------------------------------------
class twPixelShader
{
public:
	twPixelShader() = default;
	virtual ~twPixelShader() {};

	virtual void Destroy() = 0;
};