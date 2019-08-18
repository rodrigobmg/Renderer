#pragma once

#include <General/FrameConstantBuffer.h>
#include "DXConstantBuffer.h"

class DXFrameConstantBuffer : public FrameConstantBuffer, public DXConstantBuffer
{
public:
	DXFrameConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext);
	~DXFrameConstantBuffer();

	virtual bool SetData(const void* data);
};