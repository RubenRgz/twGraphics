/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twBuffer.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Buffer class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// BUFFER CLASS
//--------------------------------------------------------------------------------------
class twBuffer
{
public:
	twBuffer() = default;
	virtual ~twBuffer() {};

	virtual void Destroy() = 0;
};