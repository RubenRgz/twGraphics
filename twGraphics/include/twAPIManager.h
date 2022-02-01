/************************************************************************/
/**
* @LC	  13/08/2020
* @file   twAPIManager.h
* @Author Rubén Rodríguez (rubn2113@gmail.com)
* @date   05/06/2020
* @brief  Manages the current graphic API
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// DEFINES
//--------------------------------------------------------------------------------------
#define SAFE_RELEASE(x) { if(x){x->Release(); x = nullptr;} }

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twPlatformTypes.h"
#include "twModule.h"
#include "twGraphicDataStructure.h"
#include "twRenderTargetView.h"
#include "twTexture2D.h"
#include "twDepthStencilView.h"
#include "twVertexShader.h"
#include "twInputLayout.h"
#include "twPixelShader.h"
#include "twBuffer.h"
#include "twSamplerState.h"
#include "twShaderResourceView.h"
#include <vector>

//--------------------------------------------------------------------------------------
// USINGS
//--------------------------------------------------------------------------------------
using std::string;
using std::vector;
using std::shared_ptr; 
using std::make_shared;
using std::dynamic_pointer_cast;

//--------------------------------------------------------------------------------------
// GRAPHICS API MANAGER CLASS
//--------------------------------------------------------------------------------------
class twAPIManager : public twModule<twAPIManager>
{
private:
	void* m_ptrWindow = nullptr;
	uint32 m_Width;
	uint32 m_Height;

	ID3D11Device* m_ptrDevice = nullptr;
	ID3D11DeviceContext* m_ptrContext = nullptr;
	IDXGISwapChain* m_ptrSwapChain = nullptr;
	ID3DBlob * m_ptrVSBlob;
	ID3DBlob * m_ptrPSBlob;

	shared_ptr<twRenderTargetView> m_ptrBackBufferRTV;
	shared_ptr<twDepthStencilView> m_ptrDepthStencilView;
	shared_ptr<twSamplerState> m_ptrSamplerState;

public:
	twAPIManager(void* _ptrWindow);
	virtual ~twAPIManager() {};

	void onInit();
	void onDestroy();

	void Update();
	void Render();
	void Resize(uint32 _width, uint32 _height);

	shared_ptr<twRenderTargetView> GetBackBufferRTV();
	shared_ptr<twDepthStencilView> GetDSV();
	shared_ptr<twSamplerState> GetSamplerState();

	// DEVICE FUNCTIONS
	shared_ptr<twRenderTargetView> CreateRenderTargetView(
												const twRenderTargetViewData& _refData);

	shared_ptr<twTexture2D> LoadTexture2D(const string& _refPath);

	shared_ptr<twTexture2D> CreateTexture2D(const twTexture2DData& _refData);

	shared_ptr<twVertexShader> CreateVertexShaderFromFile(
												const twVertexShaderData& _refData);

	shared_ptr<twInputLayout> ReflectInputLayout();

	shared_ptr<twPixelShader> CreatePixelShaderFromFile(const twPixelShaderData& _refData);

	shared_ptr<twBuffer> CreateBuffer(const twBufferData& _refData);

	shared_ptr<twShaderResourceView> CreateShaderResourceView(
												const twShaderResourceViewData& _refData);

	// DEVICE CONTEXT FUNCTIONS
	void UpdateSubresource(void* _ptrResource, const void* _ptrSrcData);

	void SetRenderTargets(uint32 _numViews, shared_ptr<twRenderTargetView> _ptrRtv, 
					      shared_ptr<twDepthStencilView> _ptrDsv);

	void SetInputLayout(shared_ptr<twInputLayout> _ptrInputLayout);

	void SetVertexBuffers(twBuffer* _ptrBuffer, uint32 _strides);

	void SetIndexBuffer(twBuffer* _ptrBuffer, twFormat _format);

	void SetPrimitiveTopology(const twPrimitiveTopology& _topology);

	void SetViewports(uint32 _numViewports, const twViewportData& _refData);

	void SetVertexShader(shared_ptr<twVertexShader> _ptrVS, uint32 _numClassInstances);

	void SetVSConstantBuffers(uint32 _startSlot, uint32 _numBuffers, 
						      shared_ptr<twBuffer> _buffer);

	void SetPSConstantBuffers(uint32 _startSlot, uint32 _numBuffers, 
							  shared_ptr<twBuffer> _buffer);

	void SetPixelShader(shared_ptr<twPixelShader> _ptrPS, uint32 _numClassInstances);

	void SetPSShaderResources(uint32 _startSlot, uint32 _numViews,
							  shared_ptr<twShaderResourceView> _ptrSRV);

	void SetPSSamplers(uint32 _startSlot, uint32 _numSamplers, 
					   shared_ptr<twSamplerState> _ptrSamplers);

	void ClearRenderTargetView(shared_ptr<twRenderTargetView> _ptrRtv, 
						       const float* _ptrColor);

	void ClearDepthStencilView(shared_ptr<twDepthStencilView> _ptrDsv, twClearFlag _flag,
							   float _depth, uint8 _stencil);
	void ClearState();

	void DrawIndexed(uint32 _indexCount, uint32 _startIndexLocation,
				     int32 _baseVertexLocation);

	void Draw(uint32 _vertexCount, uint32 _startVertexLocation);

	// SWAP CHAIN FUNCTIONS
	void Present();

private: 
	void CreateDevice();
	void CreateDeviceContext();
	void CreateSwapChain();
	void GetBackAndFrontBuffer();
	void CreateDepthStencilView();
	void CreateSamplerState();
};
