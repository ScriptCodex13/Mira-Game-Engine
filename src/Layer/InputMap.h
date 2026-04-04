#pragma once 

#ifndef INPUTMAP_H
#define INPUTMAP_H

#include <unordered_map>
#include <magic_enum.hpp>

#include <Zap.h>

class Inputmap
{
public:
	Inputmap() 
	{
		for (auto i : magic_enum::enum_values<zap::Key>())
		{
			int pos = (int)i;
			m_map[pos] = -1;
		}
	};

	~Inputmap() {};

	void WriteKey(int key, int type) { m_map[key] = type; };
	std::unordered_map<int, int> GetMap() { return m_map; };

private:
	std::unordered_map<int, int> m_map;
};


#endif
