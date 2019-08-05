#pragma once

#include <General/Math/Math.h>

class IMesh
{
public:
	virtual ~IMesh() {};

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;
	virtual void Render() = 0;
	virtual int GetIndexCount() const = 0;

protected:
	struct VertexType
	{
		Vector3d position;
		Vector4d color;
	};
};