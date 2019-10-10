#pragma once

#include <General/Application/IInputMap.h>

class DX11InputMap : public IInputMap
{
public:
	DX11InputMap();
	~DX11InputMap() {}

	virtual unsigned int GetMappedValue(unsigned int key) const override { assert(m_keyMap.find(key) != m_keyMap.end()); return m_keyMap.at(key); }
private:
	std::map<unsigned int, unsigned int> m_keyMap;
};
