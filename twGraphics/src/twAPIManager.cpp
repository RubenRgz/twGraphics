#include "twAPIManager.h"
#include "twDXTexture2D.h"
#include "twDXRenderTargetView.h"
#include "twDXShaderResourceView.h"
#include "twDXVertexShader.h"
#include "twDXInputLayout.h"
#include "twDXPixelShader.h"
#include "twDXBuffer.h"
#include "twDXDepthStencilView.h"
#include "twDXSamplerState.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8
#include "stb_image.h"

// Forward declaration
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, 
							  LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

twAPIManager::twAPIManager(void* _ptrWindow)
{
	m_ptrWindow = _ptrWindow;
}

void twAPIManager::onInit()
{
	// Create obj members
	m_ptrBackBufferRTV = make_shared<twDXRenderTargetView>();
	m_ptrDepthStencilView = make_shared<twDXDepthStencilView>();
	m_ptrSamplerState = make_shared<twDXSamplerState>();

	HWND hWnd = reinterpret_cast<HWND>(m_ptrWindow);
	RECT rc;
	GetClientRect(hWnd, &rc);
	m_Width = rc.right - rc.left;
	m_Height = rc.bottom - rc.top;

	// Create Device
	CreateDevice();
	
	// Create Device Context
	CreateDeviceContext();

	// Create Swap Chain
	CreateSwapChain();

	// Create Back Buffer
	GetBackAndFrontBuffer();

	// Create Depth Stencil View
	CreateDepthStencilView();

	// Create Sampler State
	CreateSamplerState();
}

void twAPIManager::onDestroy()
{
	m_ptrWindow = nullptr;
	SAFE_RELEASE(m_ptrSwapChain);
	SAFE_RELEASE(m_ptrContext);
	SAFE_RELEASE(m_ptrDevice);
}

void twAPIManager::Update()
{
}

void twAPIManager::Render()
{

}

void twAPIManager::Resize(uint32 _width, uint32 _height)
{
	m_Height = _height;
	m_Width = _width;

	m_ptrDepthStencilView->Destroy();
	m_ptrBackBufferRTV->Destroy();

	SAFE_RELEASE(m_ptrSwapChain);

	// Create Swap Chain
	CreateSwapChain();

	// Create Back Buffer
	GetBackAndFrontBuffer();

	// Create Depth Stencil View
	CreateDepthStencilView();
}

void twAPIManager::CreateDevice()
{
	// Set Device Desc
	UINT deviceFlags = 0;
#ifdef _DEBUG
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};

	D3D_FEATURE_LEVEL m_featureLevel;
	HRESULT hr = S_OK;
	hr = D3D11CreateDevice(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		deviceFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		&m_ptrDevice,
		&m_featureLevel,
		NULL);

	if (FAILED(hr))
	{
		throw "Failed to create Device";
	}
}

void twAPIManager::CreateDeviceContext()
{
	// Create inmediate context
	m_ptrDevice->GetImmediateContext(&m_ptrContext);

	// Create deferred contex
	// ContextFlags : Reserved for future use. Pass 0.
	//m_ptrDevice->CreateDeferredContext(0, &m_ptrContext);
}

void twAPIManager::CreateSwapChain()
{
	HWND hWnd = reinterpret_cast<HWND>(m_ptrWindow);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = m_Width;
	swapChainDesc.BufferDesc.Height = m_Height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	//swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;

	// Create DXGI Device, adpter and factory
	HRESULT hr = S_OK;

	IDXGIDevice* pDXGIDevice = nullptr;
	hr = m_ptrDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);
	if (FAILED(hr))
	{
		throw "Failed to create DXGI Device";
	}

	IDXGIAdapter* pDXGIAdapter = nullptr;
	hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
	if (FAILED(hr))
	{
		throw "Failed to get Adapter";
	}

	IDXGIFactory* pIDXGIFactory = nullptr;
	hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void **)&pIDXGIFactory);
	if (FAILED(hr))
	{
		throw "Failed to get the Factory";
	}

	hr = pIDXGIFactory->CreateSwapChain(m_ptrDevice, &swapChainDesc, &m_ptrSwapChain);
	if (FAILED(hr))
	{
		throw "Failed to create Swap Chain";
	}

	SAFE_RELEASE(pIDXGIFactory);
	SAFE_RELEASE(pDXGIAdapter);
	SAFE_RELEASE(pDXGIDevice);
}

shared_ptr<twRenderTargetView> twAPIManager::GetBackBufferRTV()
{
	return m_ptrBackBufferRTV;
}

shared_ptr<twDepthStencilView> twAPIManager::GetDSV()
{
	return m_ptrDepthStencilView;
}

shared_ptr<twSamplerState> twAPIManager::GetSamplerState()
{
	return m_ptrSamplerState;
}

shared_ptr<twRenderTargetView> twAPIManager::CreateRenderTargetView(
												const twRenderTargetViewData & _refData)
{
	HRESULT hr = S_OK;
	shared_ptr<twDXRenderTargetView> tempRTV = make_shared<twDXRenderTargetView>();
	// D3D11_RENDER_TARGET_VIEW_DESC; // TODO: Hacer el desc del render target view
	hr = m_ptrDevice->CreateRenderTargetView(
		                reinterpret_cast<twDXTexture2D*>(_refData.ptrResource)->m_ptrTexture, 
						NULL,
						&tempRTV->m_ptrRenderTargetView);
	if (FAILED(hr))
	{
		throw "Failed to create Render Target View";
	}
	return tempRTV;
}

shared_ptr<twTexture2D> twAPIManager::LoadTexture2D(const string & _refPath)
{
	const std::string path(_refPath.begin(), _refPath.end());
	int width, height, channels;
	unsigned char *image = stbi_load(path.c_str(),
		&width,
		&height,
		&channels,
		STBI_rgb_alpha);

	if (NULL == image)
	{
		return false;
	}

	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA subresourceData;
	ZeroMemory(&subresourceData, sizeof(subresourceData));
	subresourceData.pSysMem = image;
	subresourceData.SysMemPitch = width * STBI_rgb_alpha;
	subresourceData.SysMemSlicePitch = width * height * STBI_rgb_alpha;

	//Create Texture
	shared_ptr<twDXTexture2D> tempTexture = make_shared<twDXTexture2D>();
	HRESULT hr = S_OK;
	hr = m_ptrDevice->CreateTexture2D(&textureDesc, &subresourceData, 
									  &tempTexture->m_ptrTexture);
	if (FAILED(hr))
	{
		throw "Cannot load Texture 2D";
	}

	// Free data
	stbi_image_free(image);

	return tempTexture;
}

shared_ptr<twTexture2D> twAPIManager::CreateTexture2D(const twTexture2DData & _refData)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = _refData.desc.width;
	textureDesc.Height = _refData.desc.height;
	textureDesc.MipLevels = _refData.desc.mipLevels;
	textureDesc.ArraySize = _refData.desc.arraySize;
	textureDesc.Format = (DXGI_FORMAT)_refData.desc.format;
	textureDesc.SampleDesc.Count = _refData.desc.count;
	textureDesc.SampleDesc.Quality = _refData.desc.quality;
	textureDesc.Usage = (D3D11_USAGE)_refData.desc.usage;
	textureDesc.BindFlags = _refData.desc.bindFlags;
	textureDesc.CPUAccessFlags = _refData.desc.cpuAccesFlags;
	textureDesc.MiscFlags = _refData.desc.miscFlags;

	if (_refData.data.hasData)
	{
		D3D11_SUBRESOURCE_DATA subresourceData;
		ZeroMemory(&subresourceData, sizeof(subresourceData));
		subresourceData.pSysMem = _refData.data.ptrMem;
		subresourceData.SysMemPitch = _refData.data.pitch;
		subresourceData.SysMemSlicePitch = _refData.data.slicePitch;

		shared_ptr<twDXTexture2D> tempTexture = make_shared<twDXTexture2D>();
		HRESULT hr = S_OK;
		m_ptrDevice->CreateTexture2D(&textureDesc, &subresourceData, 
									 &tempTexture->m_ptrTexture);
		if (FAILED(hr))
		{
			throw "Cannot create Texture 2D";
		}

		return tempTexture;
	}

	shared_ptr<twDXTexture2D> tempTexture = make_shared<twDXTexture2D>();
	HRESULT hr = S_OK;
	m_ptrDevice->CreateTexture2D(&textureDesc, NULL, &tempTexture->m_ptrTexture);
	if (FAILED(hr))
	{
		throw "Cannot create Texture 2D";
	}

	return tempTexture;
}

shared_ptr<twVertexShader> twAPIManager::CreateVertexShaderFromFile(
														const twVertexShaderData& _refData)
{
	HRESULT hr = S_OK;

	// Compile Vertex Shader
	std::wstring wfileName(_refData.fileName.begin(), _refData.fileName.end());
	const wchar_t* fileName = wfileName.c_str();

	hr = CompileShaderFromFile(const_cast<wchar_t*>(fileName), _refData.entryPoint.c_str(), 
							   _refData.shaderModel.c_str(), &m_ptrVSBlob);
	if (FAILED(hr))
	{
		throw "The FX file cannot be compiled. Please run this executable     \
				from the directory that contains the FX file.";
	}

	// Create Vertex Shader
	shared_ptr<twDXVertexShader> tempVS = make_shared<twDXVertexShader>();
	hr = m_ptrDevice->CreateVertexShader(m_ptrVSBlob->GetBufferPointer(),
										 m_ptrVSBlob->GetBufferSize(),
										 NULL, &tempVS->m_ptrVertexShader);
	if (FAILED(hr))
	{
		m_ptrVSBlob->Release();
		throw "Failed to create Vertex Shader";
	}

	return tempVS;
}

shared_ptr<twInputLayout> twAPIManager::ReflectInputLayout()
{
	// Reflect Input Layout
	HRESULT hr = S_OK;
	shared_ptr<twDXInputLayout> tempInputLayout = make_shared<twDXInputLayout>();

	// Reflect shader info
	ID3D11ShaderReflection* ptrShaderReflection = nullptr;
	hr = D3DReflect(m_ptrVSBlob->GetBufferPointer(), m_ptrVSBlob->GetBufferSize(),
					IID_ID3D11ShaderReflection,
					(void**)&ptrShaderReflection);
	if (FAILED(hr))
	{
		throw "Failed to Reflect Shader";
	}

	// Get shader info
	D3D11_SHADER_DESC shaderDesc;
	ptrShaderReflection->GetDesc(&shaderDesc);

	// Read input layout description from shader info
	vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	vector<D3D11_SIGNATURE_PARAMETER_DESC> paramListDesc;

	// Create vector with the shader size
	inputLayoutDesc.resize(shaderDesc.InputParameters);
	paramListDesc.resize(shaderDesc.InputParameters);

	// Clean all the objects
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		memset(&inputLayoutDesc[i], 0, sizeof(D3D11_INPUT_ELEMENT_DESC));
		memset(&paramListDesc[i], 0, sizeof(D3D11_SIGNATURE_PARAMETER_DESC));
	}

	// Iterate each parameter
	for (UINT i = 0; i < shaderDesc.InputParameters; ++i)
	{
		// Get description
		ptrShaderReflection->GetInputParameterDesc(i, &paramListDesc[i]);
		auto& paramDesc = paramListDesc[i];

		// Fill out input element desc
		auto& elementDesc = inputLayoutDesc[i];
		elementDesc.SemanticName = paramDesc.SemanticName;
		elementDesc.SemanticIndex = paramDesc.SemanticIndex;
		elementDesc.InputSlot = 0;
		elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate = 0;

		// Determine DXGI format
		if (paramDesc.Mask == 1)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (paramDesc.Mask <= 3)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (paramDesc.Mask <= 7)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (paramDesc.Mask <= 15)
		{
			if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	}

	// Try to create Input Layout
	hr = m_ptrDevice->CreateInputLayout(&inputLayoutDesc[0],
		inputLayoutDesc.size(), m_ptrVSBlob->GetBufferPointer(),
		m_ptrVSBlob->GetBufferSize(), &tempInputLayout->m_ptrInputLayout);

	// Free allocation shader reflection memory
	ptrShaderReflection->Release();
	ptrShaderReflection = nullptr;
	if (FAILED(hr))
	{
		throw "Failed to create Input Layout";
	}

	// Release blob data
	m_ptrVSBlob->Release();
	m_ptrVSBlob = nullptr;

	inputLayoutDesc.clear();
	paramListDesc.clear();

	return tempInputLayout;
}

shared_ptr<twPixelShader> twAPIManager::CreatePixelShaderFromFile(
														const twPixelShaderData& _refData)
{
	HRESULT hr = S_OK;

	// Compile Pixel Shader
	std::wstring wfileName(_refData.fileName.begin(), _refData.fileName.end());
	const wchar_t* fileName = wfileName.c_str();

	hr = CompileShaderFromFile(const_cast<wchar_t*>(fileName), _refData.entryPoint.c_str(),
							   _refData.shaderModel.c_str(), &m_ptrPSBlob);
	if (FAILED(hr))
	{
		throw "The FX file cannot be compiled.  Please run this executable    \
			   from the directory that contains the FX file.";
	}

	// Create Pixel Shader
	shared_ptr<twDXPixelShader> tempPS = make_shared<twDXPixelShader>();
	hr = m_ptrDevice->CreatePixelShader(m_ptrPSBlob->GetBufferPointer(),
										m_ptrPSBlob->GetBufferSize(),
									    NULL, &tempPS->m_ptrPixelShader);
	// Release blob data
	m_ptrPSBlob->Release();
	m_ptrPSBlob = nullptr;;
	if (FAILED(hr))
	{
		throw "Failed to create Vertex Shader";
	}

	return tempPS;
}

shared_ptr<twBuffer> twAPIManager::CreateBuffer(const twBufferData & _refData)
{
	D3D11_BUFFER_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Usage = (D3D11_USAGE)_refData.desc.usage;
	textureDesc.ByteWidth = _refData.desc.byteWidth;
	textureDesc.BindFlags = _refData.desc.bindFlags;
	textureDesc.CPUAccessFlags = _refData.desc.cpuAccesFlags;

	if (_refData.data.hasData)
	{
		D3D11_SUBRESOURCE_DATA subresourceData;
		ZeroMemory(&subresourceData, sizeof(subresourceData));
		subresourceData.pSysMem = _refData.data.ptrMem;
		subresourceData.SysMemPitch = _refData.data.pitch;
		subresourceData.SysMemSlicePitch = _refData.data.slicePitch;

		shared_ptr<twDXBuffer> tempBuffer = make_shared<twDXBuffer>();
		HRESULT hr = S_OK;
		m_ptrDevice->CreateBuffer(&textureDesc, &subresourceData,
			&tempBuffer->m_ptrBuffer);
		if (FAILED(hr))
		{
			throw "Cannot create Buffer";
		}

		return tempBuffer;
	}

	shared_ptr<twDXBuffer> tempBuffer = make_shared<twDXBuffer>();
	HRESULT hr = S_OK;
	m_ptrDevice->CreateBuffer(&textureDesc, NULL, &tempBuffer->m_ptrBuffer);
	if (FAILED(hr))
	{
		throw "Cannot create Buffer";
	}

	return tempBuffer;
}

shared_ptr<twShaderResourceView> twAPIManager::CreateShaderResourceView(
												const twShaderResourceViewData & _refData)
{
	HRESULT hr = S_OK;
	shared_ptr<twDXShaderResourceView> tempSRV = make_shared<twDXShaderResourceView>();
	// D3D11_RENDER_TARGET_VIEW_DESC; // TODO: Hacer el desc del render target view
	hr = m_ptrDevice->CreateShaderResourceView(
		reinterpret_cast<twDXTexture2D*>(_refData.ptrResource)->m_ptrTexture,
		NULL,
		&tempSRV->m_ptrShaderResourceView);
	if (FAILED(hr))
	{
		throw "Failed to create Shader Resource View";
	}
	return tempSRV;
}

void twAPIManager::UpdateSubresource(void* _ptrResource, const void* _ptrSrcData)
{
	m_ptrContext->UpdateSubresource(reinterpret_cast<twDXBuffer*>(_ptrResource)->m_ptrBuffer,
									0, NULL, _ptrSrcData, 0, 0);
}

void twAPIManager::SetRenderTargets(uint32 _numViews, shared_ptr<twRenderTargetView> _ptrRtv,
									shared_ptr<twDepthStencilView> _ptrDsv)
{
	m_ptrContext->OMSetRenderTargets(_numViews,
				&dynamic_pointer_cast<twDXRenderTargetView>(_ptrRtv)->m_ptrRenderTargetView,
				dynamic_pointer_cast<twDXDepthStencilView>(_ptrDsv)->m_ptrDepthStencilView);
}

void twAPIManager::SetInputLayout(shared_ptr<twInputLayout> _ptrInputLayout)
{
	m_ptrContext->IASetInputLayout(
		dynamic_pointer_cast<twDXInputLayout>(_ptrInputLayout)->m_ptrInputLayout);
}

void twAPIManager::SetVertexBuffers(twBuffer* _ptrBuffer, uint32 _strides)
{
	uint32 offset = 0;
	m_ptrContext->IASetVertexBuffers(0, 1, 
					&dynamic_cast<twDXBuffer*>(_ptrBuffer)->m_ptrBuffer, &_strides, &offset);
}

void twAPIManager::SetIndexBuffer(twBuffer* _ptrBuffer, twFormat _format)
{
	m_ptrContext->IASetIndexBuffer(dynamic_cast<twDXBuffer*>(_ptrBuffer)->m_ptrBuffer,
								   (DXGI_FORMAT)_format, 0);
}

void twAPIManager::SetPrimitiveTopology(const twPrimitiveTopology & _topology)
{
	m_ptrContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)_topology);
}

void twAPIManager::SetViewports(uint32 _numViewports, const twViewportData& _refData)
{
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)_refData.width;
	vp.Height = (FLOAT)_refData.height;
	vp.MinDepth = _refData.minDepth;
	vp.MaxDepth = _refData.maxDepth;
	vp.TopLeftX = _refData.topLeftX;
	vp.TopLeftY = _refData.topLeftY;
	m_ptrContext->RSSetViewports(_numViewports, &vp);
}

void twAPIManager::SetVertexShader(shared_ptr<twVertexShader> _ptrVS, 
								   uint32 _numClassInstances)
{
	m_ptrContext->VSSetShader(
		dynamic_pointer_cast<twDXVertexShader>(_ptrVS)->m_ptrVertexShader,
		NULL, _numClassInstances);
}

void twAPIManager::SetVSConstantBuffers(uint32 _startSlot, uint32 _numBuffers, 
										shared_ptr<twBuffer> _buffer)
{
	m_ptrContext->VSSetConstantBuffers(_startSlot, _numBuffers,
								&dynamic_pointer_cast<twDXBuffer>(_buffer)->m_ptrBuffer);
}

void twAPIManager::SetPSConstantBuffers(uint32 _startSlot, uint32 _numBuffers, 
										shared_ptr<twBuffer> _buffer)
{
	m_ptrContext->PSSetConstantBuffers(_startSlot, _numBuffers,
								&dynamic_pointer_cast<twDXBuffer>(_buffer)->m_ptrBuffer);
}

void twAPIManager::SetPixelShader(shared_ptr<twPixelShader> _ptrPS, uint32 _numClassInstances)
{
	m_ptrContext->PSSetShader(
		dynamic_pointer_cast<twDXPixelShader>(_ptrPS)->m_ptrPixelShader,
		NULL, _numClassInstances);
}

void twAPIManager::SetPSShaderResources(uint32 _startSlot, uint32 _numViews, 
									    shared_ptr<twShaderResourceView> _ptrSRV)
{
	m_ptrContext->PSSetShaderResources(_startSlot, _numViews,
		&dynamic_pointer_cast<twDXShaderResourceView>(_ptrSRV)->m_ptrShaderResourceView);
}

void twAPIManager::SetPSSamplers(uint32 _startSlot, uint32 _numSamplers, shared_ptr<twSamplerState> _ptrSamplers)
{
	m_ptrContext->PSSetSamplers(_startSlot, _numSamplers,
		&dynamic_pointer_cast<twDXSamplerState>(_ptrSamplers)->m_ptrSamplerState);
}

void twAPIManager::ClearRenderTargetView(shared_ptr<twRenderTargetView> _ptrRtv,
										 const float * _ptrColor)
{
	m_ptrContext->ClearRenderTargetView(
	dynamic_pointer_cast<twDXRenderTargetView>(_ptrRtv)->m_ptrRenderTargetView, _ptrColor);
}

void twAPIManager::ClearDepthStencilView(shared_ptr<twDepthStencilView> _ptrDsv, twClearFlag _flag,
										 float _depth, uint8 _stencil)
{
	m_ptrContext->ClearDepthStencilView(
		dynamic_pointer_cast<twDXDepthStencilView>(_ptrDsv)->m_ptrDepthStencilView,
		_flag, _depth, _stencil);
}

void twAPIManager::ClearState()
{
	m_ptrContext->ClearState();
}

void twAPIManager::DrawIndexed(uint32 _indexCount, uint32 _startIndexLocation, int32 _baseVertexLocation)
{
	m_ptrContext->DrawIndexed(_indexCount, _startIndexLocation, _baseVertexLocation);
}

void twAPIManager::Draw(uint32 _vertexCount, uint32 _startVertexLocation)
{
	m_ptrContext->Draw(_vertexCount, _startVertexLocation);
}

void twAPIManager::Present()
{
	m_ptrSwapChain->Present(0, 0);
}

void twAPIManager::GetBackAndFrontBuffer()
{
	HRESULT hr = S_OK;

	// Create a render target view with back buffer texture
	ID3D11Texture2D* ptrBackBufferTexture = nullptr;
	hr = m_ptrSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), 
								   (LPVOID*)&ptrBackBufferTexture);
	if (FAILED(hr))
	{
		throw "Failed get Back Buffer";
	}

	hr = m_ptrDevice->CreateRenderTargetView(ptrBackBufferTexture, NULL, 
	&dynamic_pointer_cast<twDXRenderTargetView>(m_ptrBackBufferRTV)->m_ptrRenderTargetView);
	if (FAILED(hr))
	{
		throw "Failed to create Back Buffer Render Target View";
	}

	// Release back buffer pointer
	SAFE_RELEASE(ptrBackBufferTexture);
}

void twAPIManager::CreateDepthStencilView()
{
	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDSVTexture;
	ZeroMemory(&descDSVTexture, sizeof(descDSVTexture));
	descDSVTexture.Width = m_Width;
	descDSVTexture.Height = m_Height;
	descDSVTexture.MipLevels = 1;
	descDSVTexture.ArraySize = 1;
	descDSVTexture.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSVTexture.SampleDesc.Count = 1;
	descDSVTexture.SampleDesc.Quality = 0;
	descDSVTexture.Usage = D3D11_USAGE_DEFAULT;
	descDSVTexture.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDSVTexture.CPUAccessFlags = 0;
	descDSVTexture.MiscFlags = 0;

	HRESULT hr = S_OK;
	ID3D11Texture2D* ptrDepthStencilTexture = nullptr;
	hr = m_ptrDevice->CreateTexture2D(&descDSVTexture, NULL, &ptrDepthStencilTexture);
	if (FAILED(hr))
	{
		throw "Failed to create Back Buffer Render Target View";
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDSVTexture.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = m_ptrDevice->CreateDepthStencilView(ptrDepthStencilTexture, &descDSV, 
	&dynamic_pointer_cast<twDXDepthStencilView>(m_ptrDepthStencilView)->m_ptrDepthStencilView);
	if (FAILED(hr))
	{
		throw "Failed to create Depth Stencil View";
	}

	// Release depth stencil pointer
	SAFE_RELEASE(ptrDepthStencilTexture);
}

void twAPIManager::CreateSamplerState()
{
	D3D11_SAMPLER_DESC descSampler;
	ZeroMemory(&descSampler, sizeof(descSampler));
	descSampler.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	descSampler.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	descSampler.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	descSampler.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	descSampler.ComparisonFunc = D3D11_COMPARISON_NEVER;
	descSampler.MinLOD = 0;
	descSampler.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = S_OK;
	hr = m_ptrDevice->CreateSamplerState(&descSampler, 
			&std::dynamic_pointer_cast<twDXSamplerState>(m_ptrSamplerState)->m_ptrSamplerState);
	if (FAILED(hr))
	{
		throw "Failed to create Depth Stencil View";
	}
}

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DCompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}
