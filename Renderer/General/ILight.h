#pragma once

class ILight
{
public:
	virtual ~ILight() {}

	virtual void SetColor(const Color& color) = 0;
	virtual const Color& GetColor() const = 0;
};