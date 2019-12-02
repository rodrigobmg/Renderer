#pragma once

#include "SceneNode.h"

class CameraNode : public SceneNode
{
public:
	CameraNode(const ICameraPtr& camera, const string& name);
	~CameraNode();

	virtual void Update() override;

	const ICameraPtr& GetCamera() const { return m_camera; }

private:
	ICameraPtr	m_camera;
};