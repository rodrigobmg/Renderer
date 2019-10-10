#pragma once

#include "ILight.h"

class Vector3d;
class Quaternion;
class IPointLight : public ILight
{
public:
	virtual ~IPointLight() {}

	virtual const Vector3d& GetWorldPosition() const = 0;
	virtual void SetPosition(const Vector3d& position) = 0;
	virtual const Quaternion& GetRotationAroundOrigin() const = 0;
	virtual void SetRotationAroundOrigin(const Quaternion& rotation) = 0;
};