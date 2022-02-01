/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twShaderResourceView.h
* @Author Rub�n Rodr�guez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Shader Resource View class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// SHADER RESOURCE VIEW CLASS
//--------------------------------------------------------------------------------------
class twShaderResourceView
{
public:
	twShaderResourceView() = default;
	virtual ~twShaderResourceView() {};

	virtual void Destroy() = 0;
};
