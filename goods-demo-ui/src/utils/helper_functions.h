#pragma once

#include "usings.h"
#include <vector>
#include "enums.h"
#include <unordered_map>

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
std::string to_string(PaymentType paymentType);
std::string to_string(const std::tm& datetime);