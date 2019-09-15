#pragma once

#include <General/ObjectConstantBuffer.h>
#include "DX11ConstantBuffer.h"

class DX11ObjectConstantBuffer : public DX11ConstantBuffer
{
public:
	DX11ObjectConstantBuffer(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext);
	DX11ObjectConstantBuffer(const DX11ObjectConstantBuffer&) = delete;
	~DX11ObjectConstantBuffer();

	virtual bool SetData(const void* data);
};