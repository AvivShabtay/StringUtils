#include <cassert>

#include "StringUtils.h"

#include <string_view>
#include <string>
#include <iostream>
#include <optional>

using namespace std::literals;

int main()
{
    // char[]
    constexpr char data[] = "Hello";
    static_assert(5 == stringUtils::stringLength(data));
    static_assert(5 == stringUtils::stringSize(data));

    // char*
    assert(5 == stringUtils::stringLength(&data[0]));
    assert(5 == stringUtils::stringSize(&data[0]));

    // wchar_t[]
    constexpr wchar_t wideData[] = L"Hello";
    static_assert(5 == stringUtils::stringLength(wideData));
    static_assert(10 == stringUtils::stringSize(wideData));

    // wchar_t*
    assert(5 == stringUtils::stringLength(&wideData[0]));
    assert(10 == stringUtils::stringSize(&wideData[0]));

    // std::string
    assert(5 == stringUtils::stringLength("hello"s));
    assert(5 == stringUtils::stringSize("hello"s));

    // std::wstring
    assert(5 == stringUtils::stringLength(L"hello"s));
    assert(10 == stringUtils::stringSize(L"hello"s));

    // std::string_view
    assert(5 == stringUtils::stringLength("hello"sv));
    assert(5 == stringUtils::stringSize("hello"sv));

    // std::wstring_view
    assert(5 == stringUtils::stringLength(L"hello"sv));
    assert(10 == stringUtils::stringSize(L"hello"sv));

    assert(L"aviv" == stringUtils::toWide("aviv"s));
    assert("aviv" == stringUtils::toMultiByte(L"aviv"s));
    assert(L"aviv" == stringUtils::toWide("aviv"sv));
    assert("aviv" == stringUtils::toMultiByte(L"aviv"sv));
    assert(L"aviv" == stringUtils::toWide("aviv"));
    assert("aviv" == stringUtils::toMultiByte(L"aviv"));

    assert("aviv" == stringUtils::toLower("AVIV"s));
    assert("aviv" == stringUtils::toLower("AVIV"sv));
    assert(L"aviv" == stringUtils::toLower(L"AVIV"s));
    assert(L"aviv" == stringUtils::toLower(L"AVIV"sv));
    //assert("aviv" == stringUtils::toLower("AVIV"));
    //assert(L"aviv" == stringUtils::toLower(L"AVIV"));

    assert("AVIV" == stringUtils::toUpper("aviv"s));
    assert("AVIV" == stringUtils::toUpper("aviv"sv));
    //assert(L"AVIV" == stringUtils::toUpper(L"aviv"));
    assert(L"AVIV" == stringUtils::toUpper(L"aviv"sv));
    //assert("AVIV" == stringUtils::toUpper("aviv"));
    //assert(L"AVIV" == stringUtils::toUpper(L"aviv"));

    return 0;
}
