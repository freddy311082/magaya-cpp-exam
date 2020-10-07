#pragma once
#include "usings.h"
#include <vector>

template <typename T>
std::vector<std::unique_ptr<T>> fromListToVector(std::list<std::unique_ptr<T>>& l)
{
	std::vector<std::unique_ptr<T>> result(l.size());

	int i = 0;
	for (auto it = l.begin(); it != l.end; ++it)
	{
		result[i++] = std::move(*it);
	}

	return result;
}