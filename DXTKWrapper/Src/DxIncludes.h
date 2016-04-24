#pragma once

//////////////////////////
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"

/////////DX10/11 Standard Defines//////////

#define DX1011_PRESENT 8

// Template for DXGI 10/11 Present function (hooked)
typedef HRESULT (WINAPI *tempPresent_Proto)(IDXGISwapChain*, UINT, UINT);

// To find in D3D10.dll
typedef HRESULT (WINAPI *tempD3D10CreateDeviceAndSwapChain)(IDXGIAdapter *pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, UINT SDKVersion, DXGI_SWAP_CHAIN_DESC *pSwapChainDesc, IDXGISwapChain **ppSwapChain, ID3D10Device **ppDevice);

// To find in D3D11.dll
typedef HRESULT (WINAPI * tempD3D11CreateDeviceAndSwapChain)(
  _In_   IDXGIAdapter *pAdapter,
  _In_   D3D_DRIVER_TYPE DriverType,
  _In_   HMODULE Software,
  _In_   UINT Flags,
  _In_   const D3D_FEATURE_LEVEL *pFeatureLevels,
  _In_   UINT FeatureLevels,
  _In_   UINT SDKVersion,
  _In_   const DXGI_SWAP_CHAIN_DESC *pSwapChainDesc,
  _Out_  IDXGISwapChain **ppSwapChain,
  _Out_  ID3D11Device **ppDevice,
  _Out_  D3D_FEATURE_LEVEL *pFeatureLevel,
  _Out_  ID3D11DeviceContext **ppImmediateContext
);

// To find in DXGI.lib
typedef HRESULT (WINAPI * tempCreateSwapChain)(
  _In_   IUnknown *pDevice,
  _In_   DXGI_SWAP_CHAIN_DESC *pDesc,
  _Out_  IDXGISwapChain **ppSwapChain
);

#define SAFE_RELEASE( x ) if( x ){ x->Release( ); x = 0; }