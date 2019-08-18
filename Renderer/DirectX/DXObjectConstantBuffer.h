#pragma once

#include <General/ObjectConstantBuffer.h>
#include "DXConstantBuffer.h"

class DXObjectConstantBuffer : public ObjectConstantBuffer, public DXConstantBuffer
{
public:
	DXObjectConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext);
	DXObjectConstantBuffer(const DXObjectConstantBuffer&) = delete;
	~DXObjectConstantBuffer();

	virtual bool SetData(const void* data);
};