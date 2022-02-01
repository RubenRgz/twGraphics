/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twVertexShader.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  Base Vertex Shader Class
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// VERTEX SHADER CLASS
//--------------------------------------------------------------------------------------
class twVertexShader
{
public:
	twVertexShader() = default;
	virtual ~twVertexShader() {};

	virtual void Destroy() = 0;
};