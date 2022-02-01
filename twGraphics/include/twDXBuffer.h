/************************************************************************/
/**
* @LC	  04/07/2020
* @file   twDXBuffer.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   30/06/2020
* @brief  DirectX Buffer
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twBuffer.h"

//--------------------------------------------------------------------------------------
// DIRECTX BUFFER CLASS
//--------------------------------------------------------------------------------------
class twDXBuffer : public twBuffer
{
private:
	ID3D11Buffer* m_ptrBuffer;

	friend class twAPIManager;

public:
	twDXBuffer() = default;
	~twDXBuffer()
	{
		Destroy();
	}

	void Destroy() override
	{
		SAFE_RELEASE(m_ptrBuffer);
	}
};

