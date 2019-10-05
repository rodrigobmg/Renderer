#pragma once

#include "ILight.h"

class Vector3d;
class IPointLight : public ILight
{
public:
	virtual ~IPointLight() {}

	virtual const Vector3d& GetPosition() const = 0;
	virtual void SetPosition(const Vector3d& position) = 0;
};