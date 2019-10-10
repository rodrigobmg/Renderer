#pragma once
#include <General/Math/Color.h>

class ILight
{
public:
	virtual ~ILight() {}

	virtual void SetColor(const Color& color) = 0;
	virtual const Color& GetColor() const = 0;
	virtual const SceneObjectPtr& GetSceneObject() const = 0;
	virtual void Render() = 0;
};