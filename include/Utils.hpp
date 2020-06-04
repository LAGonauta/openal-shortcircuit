#pragma once

#include <string>
#include <vector>

#include "Visibility.h"

DLL_LOCAL std::vector<std::string> string_unwrap(const char* oal_strings, const std::string separator);
DLL_LOCAL std::string string_join(const std::vector<std::string>& strings, const char separator);