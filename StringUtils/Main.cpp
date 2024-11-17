#include "StringUtils.h"

#include <string_view>
#include <string>
#include <iostream>

using namespace std::literals;
using namespace stringUtils;

int main()
{
    std::wcout << toWide(std::string("aviv")) << std::endl;
    std::cout << toMultiByte(std::wstring(L"aviv")) << std::endl;
    std::wcout << toWide("aviv"sv) << std::endl;
    std::cout << toMultiByte(L"aviv"sv) << std::endl;
    std::wcout << toWide("aviv") << std::endl;
    std::cout << toMultiByte(L"aviv") << std::endl;

    std::string nameUpper("AVIV");
    std::cout << toLower(nameUpper) << std::endl;
    std::wstring nameUpperWide(L"AVIV");
    std::wcout << toLower(nameUpperWide) << std::endl;
    std::cout << toLower("AVIV") << std::endl;
    std::wcout << toLower(L"AVIV") << std::endl;

    std::string nameLower("aviv");
    std::cout << toUpper(nameLower) << std::endl;
    std::wstring nameLowerWide(L"aviv");
    std::wcout << toUpper(nameLowerWide) << std::endl;
    std::cout << toUpper("aviv") << std::endl;
    std::wcout << toUpper(L"aviv") << std::endl;

    return 0;
}
