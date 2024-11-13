#pragma once

#include <string>
#include <string_view>

namespace stringConversion {

std::wstring multiByteToWide(std::string_view multiByteData);

std::string wideToMultiByte(std::wstring_view wideData);

} // namespace stringConversion
