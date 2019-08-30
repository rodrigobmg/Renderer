#pragma once

#include <General/FrameConstantBuffer.h>
#include "DX11ConstantBuffer.h"

class DX11FrameConstantBuffer : public DX11ConstantBuffer
{
public:
	DX11FrameConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext);
	~DX11FrameConstantBuffer();

	virtual bool SetData(const void* data);
};