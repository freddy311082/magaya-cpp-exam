#pragma once

#include "usings.h"
#include <vector>

template <typename T>
void listToVector(
	std::list<std::unique_ptr<T>>& l,
	std::vector<std::unique_ptr<T>>& result)
{
	result.clear();
	result.resize(l.size());

	int i = 0;
	for (auto& u_ptr: l)
	{
		result[i++] = std::move(u_ptr);
	}
}



bool strToDouble(const std::string& str, double& result);