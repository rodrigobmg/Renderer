#pragma once

#include "ILight.h"

class IPointLight : public ILight
{
public:
	virtual ~IPointLight() {}

	virtual const Vector3d& GetPosition() const = 0;
};