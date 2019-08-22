#pragma once
#include "ICamera.h"

class Camera : public ICamera
{
public:
	Camera();
	Camera(const Camera& camera) = delete;
	~Camera();

	virtual const Matrix4d& GetViewMatrix() override;
	virtual const Transform& GetTransform() const override { return m_transform; }
	virtual void SetTransform(const Transform& transform) override { m_transform = transform; }

private:
	Matrix4d	m_viewMatrix;
	Transform	m_transform;
};