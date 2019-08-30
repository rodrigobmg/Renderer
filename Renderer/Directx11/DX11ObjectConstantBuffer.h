#pragma once

#include <General/ObjectConstantBuffer.h>
#include "DX11ConstantBuffer.h"

class DX11ObjectConstantBuffer : public DX11ConstantBuffer
{
public:
	DX11ObjectConstantBuffer(std::unique_ptr<ID3D11Device>& device, std::unique_ptr<ID3D11DeviceContext>& deviceContext);
	DX11ObjectConstantBuffer(const DX11ObjectConstantBuffer&) = delete;
	~DX11ObjectConstantBuffer();

	virtual bool SetData(const void* data);
};