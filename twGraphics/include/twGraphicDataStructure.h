/************************************************************************/
/**
* @LC	  03/07/2020
* @file   twGraphicDataStructure.h
* @Author Rub�n Rodr�guez (rubn2113@gmail.com)
* @date   05/06/2020
* @brief  Stores all the own object types we gonna use
* @bug	  No know Bugs
*/
/************************************************************************/
#pragma once

//--------------------------------------------------------------------------------------
// INCLUDES
//--------------------------------------------------------------------------------------
#include "twPlatformTypes.h"
#include "twTexture2D.h"
#include "twBuffer.h"

//--------------------------------------------------------------------------------------
// USINGS
//--------------------------------------------------------------------------------------
using twBlob = ID3DBlob;
using std::string;

//--------------------------------------------------------------------------------------
// ENUMS
//--------------------------------------------------------------------------------------
enum twFormat
{
	tw_FORMAT_UNKNOWN = DXGI_FORMAT_UNKNOWN,
	tw_FORMAT_R32G32B32A32_TYPELESS = DXGI_FORMAT_R32G32B32A32_TYPELESS,
	tw_FORMAT_R32G32B32A32_FLOAT = DXGI_FORMAT_R32G32B32A32_FLOAT,
	tw_FORMAT_R32G32B32A32_UINT = DXGI_FORMAT_R32G32B32A32_UINT,
	tw_FORMAT_R32G32B32A32_SINT = DXGI_FORMAT_R32G32B32A32_SINT,
	tw_FORMAT_R32G32B32_TYPELESS = DXGI_FORMAT_R32G32B32_TYPELESS,
	tw_FORMAT_R32G32B32_FLOAT = DXGI_FORMAT_R32G32B32_FLOAT,
	tw_FORMAT_R32G32B32_UINT = DXGI_FORMAT_R32G32B32_UINT,
	tw_FORMAT_R32G32B32_SINT = DXGI_FORMAT_R32G32B32_SINT,
	tw_FORMAT_R16G16B16A16_TYPELESS = DXGI_FORMAT_R16G16B16A16_TYPELESS,
	tw_FORMAT_R16G16B16A16_FLOAT = DXGI_FORMAT_R16G16B16A16_FLOAT,
	tw_FORMAT_R16G16B16A16_UNORM = DXGI_FORMAT_R16G16B16A16_UNORM,
	tw_FORMAT_R16G16B16A16_UINT = DXGI_FORMAT_R16G16B16A16_UINT,
	tw_FORMAT_R16G16B16A16_SNORM = DXGI_FORMAT_R16G16B16A16_SNORM,
	tw_FORMAT_R16G16B16A16_SINT = DXGI_FORMAT_R16G16B16A16_SINT,
	tw_FORMAT_R32G32_TYPELESS = DXGI_FORMAT_R32G32_TYPELESS,
	tw_FORMAT_R32G32_FLOAT = DXGI_FORMAT_R32G32_FLOAT,
	tw_FORMAT_R32G32_UINT = DXGI_FORMAT_R32G32_UINT,
	tw_FORMAT_R32G32_SINT = DXGI_FORMAT_R32G32_SINT,
	tw_FORMAT_R32G8X24_TYPELESS = DXGI_FORMAT_R32G8X24_TYPELESS,
	tw_FORMAT_D32_FLOAT_S8X24_UINT = DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
	tw_FORMAT_R32_FLOAT_X8X24_TYPELESS = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
	tw_FORMAT_X32_TYPELESS_G8X24_UINT = DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
	tw_FORMAT_R10G10B10A2_TYPELESS = DXGI_FORMAT_R10G10B10A2_TYPELESS,
	tw_FORMAT_R10G10B10A2_UNORM = DXGI_FORMAT_R10G10B10A2_UNORM,
	tw_FORMAT_R10G10B10A2_UINT = DXGI_FORMAT_R10G10B10A2_UINT,
	tw_FORMAT_R11G11B10_FLOAT = DXGI_FORMAT_R11G11B10_FLOAT,
	tw_FORMAT_R8G8B8A8_TYPELESS = DXGI_FORMAT_R8G8B8A8_TYPELESS,
	tw_FORMAT_R8G8B8A8_UNORM = DXGI_FORMAT_R8G8B8A8_UNORM,
	tw_FORMAT_R8G8B8A8_UNORM_SRGB = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
	tw_FORMAT_R8G8B8A8_UINT = DXGI_FORMAT_R8G8B8A8_UINT,
	tw_FORMAT_R8G8B8A8_SNORM = DXGI_FORMAT_R8G8B8A8_SNORM,
	tw_FORMAT_R8G8B8A8_SINT = DXGI_FORMAT_R8G8B8A8_SINT,
	tw_FORMAT_R16G16_TYPELESS = DXGI_FORMAT_R16G16_TYPELESS,
	tw_FORMAT_R16G16_FLOAT = DXGI_FORMAT_R16G16_FLOAT,
	tw_FORMAT_R16G16_UNORM = DXGI_FORMAT_R16G16_UNORM,
	tw_FORMAT_R16G16_UINT = DXGI_FORMAT_R16G16_UINT,
	tw_FORMAT_R16G16_SNORM = DXGI_FORMAT_R16G16_SNORM,
	tw_FORMAT_R16G16_SINT = DXGI_FORMAT_R16G16_SINT,
	tw_FORMAT_R32_TYPELESS = DXGI_FORMAT_R32_TYPELESS,
	tw_FORMAT_D32_FLOAT = DXGI_FORMAT_D32_FLOAT,
	tw_FORMAT_R32_FLOAT = DXGI_FORMAT_R32_FLOAT,
	tw_FORMAT_R32_UINT = DXGI_FORMAT_R32_UINT,
	tw_FORMAT_R32_SINT = DXGI_FORMAT_R32_SINT,
	tw_FORMAT_R24G8_TYPELESS = DXGI_FORMAT_R24G8_TYPELESS,
	tw_FORMAT_D24_UNORM_S8_UINT = DXGI_FORMAT_D24_UNORM_S8_UINT,
	tw_FORMAT_R24_UNORM_X8_TYPELESS = DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
	tw_FORMAT_X24_TYPELESS_G8_UINT = DXGI_FORMAT_X24_TYPELESS_G8_UINT,
	tw_FORMAT_R8G8_TYPELESS = DXGI_FORMAT_R8G8_TYPELESS,
	tw_FORMAT_R8G8_UNORM = DXGI_FORMAT_R8G8_UNORM,
	tw_FORMAT_R8G8_UINT = DXGI_FORMAT_R8G8_UINT,
	tw_FORMAT_R8G8_SNORM = DXGI_FORMAT_R8G8_SNORM,
	tw_FORMAT_R8G8_SINT = DXGI_FORMAT_R8G8_SINT,
	tw_FORMAT_R16_TYPELESS = DXGI_FORMAT_R16_TYPELESS,
	tw_FORMAT_R16_FLOAT = DXGI_FORMAT_R16_FLOAT,
	tw_FORMAT_D16_UNORM = DXGI_FORMAT_D16_UNORM,
	tw_FORMAT_R16_UNORM = DXGI_FORMAT_R16_UNORM,
	tw_FORMAT_R16_UINT = DXGI_FORMAT_R16_UINT,
	tw_FORMAT_R16_SNORM = DXGI_FORMAT_R16_SNORM,
	tw_FORMAT_R16_SINT = DXGI_FORMAT_R16_SINT,
	tw_FORMAT_R8_TYPELESS = DXGI_FORMAT_R8_TYPELESS,
	tw_FORMAT_R8_UNORM = DXGI_FORMAT_R8_UNORM,
	tw_FORMAT_R8_UINT = DXGI_FORMAT_R8_UINT,
	tw_FORMAT_R8_SNORM = DXGI_FORMAT_R8_SNORM,
	tw_FORMAT_R8_SINT = DXGI_FORMAT_R8_SINT,
	tw_FORMAT_A8_UNORM = DXGI_FORMAT_A8_UNORM,
	tw_FORMAT_R1_UNORM = DXGI_FORMAT_R1_UNORM,
	tw_FORMAT_R9G9B9E5_SHAREDEXP = DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
	tw_FORMAT_R8G8_B8G8_UNORM = DXGI_FORMAT_R8G8_B8G8_UNORM,
	tw_FORMAT_G8R8_G8B8_UNORM = DXGI_FORMAT_G8R8_G8B8_UNORM,
	tw_FORMAT_BC1_TYPELESS = DXGI_FORMAT_BC1_TYPELESS,
	tw_FORMAT_BC1_UNORM = DXGI_FORMAT_BC1_UNORM,
	tw_FORMAT_BC1_UNORM_SRGB = DXGI_FORMAT_BC1_UNORM_SRGB,
	tw_FORMAT_BC2_TYPELESS = DXGI_FORMAT_BC2_TYPELESS,
	tw_FORMAT_BC2_UNORM = DXGI_FORMAT_BC2_UNORM,
	tw_FORMAT_BC2_UNORM_SRGB = DXGI_FORMAT_BC2_UNORM_SRGB,
	tw_FORMAT_BC3_TYPELESS = DXGI_FORMAT_BC3_TYPELESS,
	tw_FORMAT_BC3_UNORM = DXGI_FORMAT_BC3_UNORM,
	tw_FORMAT_BC3_UNORM_SRGB = DXGI_FORMAT_BC3_UNORM_SRGB,
	tw_FORMAT_BC4_TYPELESS = DXGI_FORMAT_BC4_TYPELESS,
	tw_FORMAT_BC4_UNORM = DXGI_FORMAT_BC4_UNORM,
	tw_FORMAT_BC4_SNORM = DXGI_FORMAT_BC4_SNORM,
	tw_FORMAT_BC5_TYPELESS = DXGI_FORMAT_BC5_TYPELESS,
	tw_FORMAT_BC5_UNORM = DXGI_FORMAT_BC5_UNORM,
	tw_FORMAT_BC5_SNORM = DXGI_FORMAT_BC5_SNORM,
	tw_FORMAT_B5G6R5_UNORM = DXGI_FORMAT_B5G6R5_UNORM,
	tw_FORMAT_B5G5R5A1_UNORM = DXGI_FORMAT_B5G5R5A1_UNORM,
	tw_FORMAT_B8G8R8A8_UNORM = DXGI_FORMAT_B8G8R8A8_UNORM,
	tw_FORMAT_B8G8R8X8_UNORM = DXGI_FORMAT_B8G8R8X8_UNORM,
	tw_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
	tw_FORMAT_B8G8R8A8_TYPELESS = DXGI_FORMAT_B8G8R8A8_TYPELESS,
	tw_FORMAT_B8G8R8A8_UNORM_SRGB = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
	tw_FORMAT_B8G8R8X8_TYPELESS = DXGI_FORMAT_B8G8R8X8_TYPELESS,
	tw_FORMAT_B8G8R8X8_UNORM_SRGB = DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
	tw_FORMAT_BC6H_TYPELESS = DXGI_FORMAT_BC6H_TYPELESS,
	tw_FORMAT_BC6H_UF16 = DXGI_FORMAT_BC6H_UF16,
	tw_FORMAT_BC6H_SF16 = DXGI_FORMAT_BC6H_SF16,
	tw_FORMAT_BC7_TYPELESS = DXGI_FORMAT_BC7_TYPELESS,
	tw_FORMAT_BC7_UNORM = DXGI_FORMAT_BC7_UNORM,
	tw_FORMAT_BC7_UNORM_SRGB = DXGI_FORMAT_BC7_UNORM_SRGB,
	tw_FORMAT_FORCE_UINT = DXGI_FORMAT_FORCE_UINT
};

enum twUsage
{
	tw_USAGE_DEFAULT = D3D11_USAGE_DEFAULT,
	tw_USAGE_IMMUTABLE = D3D11_USAGE_IMMUTABLE,
	tw_USAGE_DYNAMIC = D3D11_USAGE_DYNAMIC,
	tw_USAGE_STAGING = D3D11_USAGE_STAGING
};

enum twBindFlags
{
	tw_BIND_VERTEX_BUFFER = D3D11_BIND_VERTEX_BUFFER,
	tw_BIND_INDEX_BUFFER = D3D11_BIND_INDEX_BUFFER,
	tw_BIND_CONSTANT_BUFFER = D3D11_BIND_CONSTANT_BUFFER,
	tw_BIND_SHADER_RESOURCE = D3D11_BIND_SHADER_RESOURCE,
	tw_BIND_STREAM_OUTPUT = D3D11_BIND_STREAM_OUTPUT,
	tw_BIND_RENDER_TARGET = D3D11_BIND_RENDER_TARGET,
	tw_BIND_DEPTH_STENCIL = D3D11_BIND_DEPTH_STENCIL,
	tw_BIND_UNORDERED_ACCESS = D3D11_BIND_UNORDERED_ACCESS
};

enum twPrimitiveTopology
{
	tw_PRIMITIVE_TOPOLOGY_UNDEFINED = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
	tw_PRIMITIVE_TOPOLOGY_POINTLIST = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
	tw_PRIMITIVE_TOPOLOGY_LINELIST = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
	tw_PRIMITIVE_TOPOLOGY_LINESTRIP = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
	tw_PRIMITIVE_TOPOLOGY_TRIANGLELIST = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
	tw_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
	tw_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
	tw_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
	tw_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
	tw_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
	tw_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
	tw_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST
};

enum twClearFlag
{
	tw_CLEAR_DEPTH = D3D11_CLEAR_DEPTH,
	tw_CLEAR_STENCIL = D3D11_CLEAR_STENCIL
};

//D3D11_CLEAR_FLAG

//--------------------------------------------------------------------------------------
// DATA STRUCTURE
//--------------------------------------------------------------------------------------
struct twSubResourceData
{
	bool hasData;
	const void* ptrMem;
	uint32 pitch;
	uint32 slicePitch;
};

struct twTexture2DDesc
{
	uint32 width;
	uint32 height;
	uint32 mipLevels;
	uint32 arraySize;
	twFormat format;
	uint32 count;
	uint32 quality;
	twUsage usage;
	uint32 bindFlags;
	uint32 cpuAccesFlags;
	uint32 miscFlags;
};

struct twTexture2DData
{
	twTexture2DDesc desc;
	twSubResourceData data;
};

struct twRenderTargetViewData
{
	void* ptrResource;
};

struct twShaderResourceViewData
{
	void* ptrResource;
};

struct twBufferDesc
{
	uint32 byteWidth;
	twUsage usage;
	uint32 bindFlags;
	uint32 cpuAccesFlags;
	uint32 miscFlags;
	uint32 structureByteStride;
};

struct twBufferData
{
	twBufferDesc desc;
	twSubResourceData data;
};

struct twViewportData
{
	float topLeftX;
	float topLeftY;
	float width;
	float height;
	float minDepth;
	float maxDepth;
};

struct twVertexShaderData
{
	string fileName;
	string entryPoint;
	string shaderModel;
};

struct twPixelShaderData
{
	string fileName;
	string entryPoint;
	string shaderModel;
};
