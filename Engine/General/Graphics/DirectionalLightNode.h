#pragma once

#include "SceneNode.h"

class DirectionalLight;
class DirectionalLightNode : public SceneNode
{
public:
	DirectionalLightNode(const SharedPtr<DirectionalLight>& directionalLight, const string& name);
	~DirectionalLightNode();

	virtual void Update();
	const SharedPtr<DirectionalLight>& GetLight() const { return m_directionalLight; }

private:
	SharedPtr<DirectionalLight>	m_directionalLight;
};