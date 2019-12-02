#include "pch.h"
#include "CameraNode.h"

#include "ICamera.h"

CameraNode::CameraNode(const ICameraPtr& camera, const string& name)
	: SceneNode(name, SceneNodeType::kCamera)
	, m_camera(camera)
{
	Matrix4d parentMatrixInv = Math::MatrixInverse(GetParentMatrix());
	Matrix4d mat = m_camera->GetTransform().GetMatrix();
	mat = mat * parentMatrixInv;
	m_localTransform.Set(mat);
}

CameraNode::~CameraNode()
{
}

void CameraNode::Update()
{
	SceneNode::Update();
	m_camera->SetTransform(m_localTransform.GetMatrix() * GetParentMatrix());
}
