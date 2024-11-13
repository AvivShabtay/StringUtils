#include "StringUtils.h"

#include <string>
#include <string_view>
#include <iostream>

using namespace stringUtils;

int main()
{
    std::wcout << toWide(std::string("aviv")) << std::endl;
    std::cout << toMultiByte(std::wstring(L"aviv")) << std::endl;
    std::wcout << toWide(std::string_view("aviv")) << std::endl;
    std::cout << toMultiByte(std::wstring_view(L"aviv")) << std::endl;
    std::wcout << toWide("aviv") << std::endl;
    std::cout << toMultiByte(L"aviv") << std::endl;

    return 0;
}
