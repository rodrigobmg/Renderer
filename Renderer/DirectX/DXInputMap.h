#pragma once

#include <General/IInputMap.h>

class DXInputMap : public IInputMap
{
public:
	DXInputMap();
	~DXInputMap() {}

	virtual unsigned int GetMappedValue(unsigned int key) const  override { assert(m_keyMap.find(key) != m_keyMap.end()); return m_keyMap.at(key); }
private:
	std::map<unsigned int, unsigned int> m_keyMap;
};
