#pragma once

class ICamera
{
public:
	virtual ~ICamera() {}

	virtual const Matrix4d& GetViewMatrix() = 0;
	virtual const Transform& GetTransform() const = 0;
	virtual void SetTransform(const Transform& transform) = 0;
};