//--------------------------------------------------------------------------------------
// File: pch.h
//
// Header for standard system include files.
//
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
//--------------------------------------------------------------------------------------

#pragma once

#pragma warning(disable : 4619 4616 26812)
// C4619/4616 #pragma warning warnings
// 26812: The enum type 'x' is unscoped. Prefer 'enum class' over 'enum' (Enum.3).

// Use the C++ standard templated min/max
#define NOMINMAX

#include <winapifamily.h>

#if defined(_XBOX_ONE) && defined(_TITLE)
#error Support for Xbox One has been retired.
#else

#include <winsdkver.h>
#define _WIN32_WINNT 0x0A00
#include <sdkddkver.h>

#pragma warning(push)
#pragma warning(disable : 4005)
#define NOMINMAX
#define NODRAWTEXT
#define NOBITMAP
#define NOMCX
#define NOSERVICE
#define NOHELP
#define WIN32_LEAN_AND_MEAN
#pragma warning(pop)

#include <Windows.h>
#endif

#include <wrl/client.h>
#include <wrl/event.h>

#define D3DX12_NO_STATE_OBJECT_HELPERS
#define D3DX12_NO_CHECK_FEATURE_SUPPORT_CLASS

#ifdef _GAMING_XBOX_SCARLETT
#include <d3d12_xs.h>
#include <d3dx12_xs.h>
#elif (defined(_XBOX_ONE) && defined(_TITLE)) || defined(_GAMING_XBOX)
#include <d3d12_x.h>
#include <d3dx12_x.h>
#else
#include <directx/dxgiformat.h>
#include <directx/d3d12.h>
#include <directx/d3dx12.h>
#include <dxguids/dxguids.h>

#include <dxgi1_6.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif
#endif

#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cwchar>
#include <exception>
#include <iterator>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <system_error>
#include <tuple>
#include <vector>

#include <pix.h>

namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) noexcept : result(hr) {}

        const char* what() const override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
#ifdef _DEBUG
            char str[64] = {};
            sprintf_s(str, "**ERROR** Fatal Error with HRESULT of %08X\n", static_cast<unsigned int>(hr));
            OutputDebugStringA(str);
            __debugbreak();
#endif
            throw com_exception(hr);
        }
    }
}

#define DIRECTX_TOOLKIT_IMPORT
#include <directxtk12/CommonStates.h>
#include <directxtk12/DDSTextureLoader.h>
#include <directxtk12/DescriptorHeap.h>
#include <directxtk12/DirectXHelpers.h>
#include <directxtk12/Effects.h>
#include <directxtk12/GamePad.h>
#include <directxtk12/GraphicsMemory.h>
#include <directxtk12/Keyboard.h>
#include <directxtk12/Model.h>
#include <directxtk12/Mouse.h>
#include <directxtk12/PostProcess.h>
#include <directxtk12/PrimitiveBatch.h>
#include <directxtk12/ResourceUploadBatch.h>
#include <directxtk12/SimpleMath.h>
#include <directxtk12/SpriteBatch.h>
#include <directxtk12/SpriteFont.h>
#include <directxtk12/VertexTypes.h>
