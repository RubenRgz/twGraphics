/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twInputLayout.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Input Layout class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INPUT LAYOUT CLASS
//--------------------------------------------------------------------------------------
class twInputLayout
{
public:
	twInputLayout() = default;
	virtual ~twInputLayout() {};

	virtual void Destroy() = 0;
};