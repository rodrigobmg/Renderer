#pragma once

#include "ILight.h"

class IDirectionalLight
{
public:
	virtual ~IDirectionalLight() {}

	virtual Vector3d GetDirection() const = 0;
};