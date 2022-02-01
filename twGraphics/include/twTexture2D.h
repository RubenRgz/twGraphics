/************************************************************************/
/**
* @LC	  02/07/2020
* @file   twTexture2D.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Texture 2D class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// TEXTURE 2D CLASS
//--------------------------------------------------------------------------------------
class twTexture2D
{
public:
	twTexture2D() = default;
	virtual ~twTexture2D() {};

	virtual void Destroy() = 0;
};
