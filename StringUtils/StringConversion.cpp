#include "StringConversion.h"

#include <Windows.h>

namespace stringConversion {

std::wstring multiByteToWide(const std::string_view multiByteData)
{
	if (0 == multiByteData.length())
	{
		return std::wstring();
	}

	// Compute the length of the buffer.
	const int charCount = MultiByteToWideChar(
		CP_UTF8, 0,
		multiByteData.data(), static_cast<int>(multiByteData.length()),
		nullptr, 0);

	if (charCount == 0)
	{
		return std::wstring();
	}

	std::wstring wideData;
	wideData.resize(static_cast<size_t>(charCount));

	MultiByteToWideChar(CP_UTF8, 0,
	                    multiByteData.data(), static_cast<int>(multiByteData.length()),
	                    wideData.data(), charCount);

	return wideData;
}

std::string wideToMultiByte(const std::wstring_view wideData)
{
	if (0 == wideData.length())
	{
		return std::string();
	}

	// Compute the length of the buffer.
	const int charCount = WideCharToMultiByte(
		CP_UTF8, 0,
		wideData.data(), static_cast<int>(wideData.length()),
		nullptr, 0,
		nullptr, nullptr);

	if (charCount == 0)
	{
		return std::string();
	}

	std::string multiByteData;
	multiByteData.resize(static_cast<size_t>(charCount));

	WideCharToMultiByte(
		CP_UTF8, 0,
		wideData.data(), static_cast<int>(wideData.length()),
		multiByteData.data(), charCount,
		nullptr, nullptr);

	return multiByteData;
}

} // namespace stringConversion
