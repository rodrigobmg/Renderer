#pragma once
#include "DX11ConstantBuffer.h"

class DX11MaterialConstantBuffer : public DX11ConstantBuffer
{
public:
	DX11MaterialConstantBuffer(const UniquePtr<ID3D11Device>& device, const UniquePtr<ID3D11DeviceContext>& deviceContext);
	~DX11MaterialConstantBuffer() {}

	virtual bool SetData(const void* data) override;
};