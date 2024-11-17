#pragma once

#include "StringConversion.h"

#include <type_traits>
#include <ranges>
#include <algorithm>

namespace stringUtils {

namespace detail {

template <typename T, typename ArrayType>
constexpr bool IsArrayOf = std::conjunction_v<
    std::is_array<T>,
    std::is_same<std::remove_extent_t<T>, ArrayType>>;

template <typename T, typename ArrayType>
struct IsArrayOfType : std::bool_constant<IsArrayOf<T, ArrayType>> {};

template <typename Type, typename CharType>
concept String = std::disjunction_v<
    std::is_same<std::remove_cvref_t<Type>, std::basic_string<CharType>>,
    std::is_same<std::remove_cvref_t<Type>, std::basic_string_view<CharType>>,
    IsArrayOfType<std::remove_cvref_t<Type>, CharType>>;

template <typename Type>
concept CharString = String<Type, char>;

template <typename Type>
concept WideCharString = String<Type, wchar_t>;

template <typename EnumType, typename... Enums>
    requires (std::is_same_v<EnumType, Enums> && ...)
constexpr bool isOneOf(EnumType value, Enums... valuesToCompare)
{
    return ((value == valuesToCompare) || ...);
}

} // namespace detail

class StringStrategySelector
{
protected:
    enum class Strategy
    {
        None,
        CharBasicString,
        WideCharBasicString,
        CharStringView,
        WideCharStringView,
        CharArray,
        WideCharArray
    };

    template <typename Type>
    static consteval Strategy choose() noexcept
    {
        using UnrefType = std::remove_cvref_t<Type>;

        if constexpr (std::same_as<UnrefType, std::basic_string<char>>) {
            return Strategy::CharBasicString;
        }
        if constexpr (std::same_as<UnrefType, std::basic_string<wchar_t>>) {
            return Strategy::WideCharBasicString;
        }
        else if constexpr (std::same_as<UnrefType, std::basic_string_view<char>>) {
            return Strategy::CharStringView;
        }
        else if constexpr (std::same_as<UnrefType, std::basic_string_view<wchar_t>>) {
            return Strategy::WideCharStringView;
        }
        else if constexpr (detail::IsArrayOf<UnrefType, char>)
        {
            return Strategy::CharArray;
        }
        else if constexpr (detail::IsArrayOf<UnrefType, wchar_t>)
        {
            return Strategy::WideCharArray;
        }
        else {
            return Strategy::None;
        }
    }

    template <typename Type>
    static constexpr Strategy choice = choose<Type>();
};

struct ToWide : StringStrategySelector
{
    template <detail::CharString StringType>
        requires (choice<StringType> != Strategy::None)
    [[nodiscard]] std::wstring operator()(const StringType& str) const
    {
        constexpr Strategy strategy = choice<StringType>;

        if constexpr (detail::isOneOf(strategy,
            Strategy::CharBasicString,
            Strategy::CharStringView,
            Strategy::CharArray))
        {
            return stringConversion::multiByteToWide(str);
        }
        else
        {
            static_assert(std::_Always_false<StringType>, "Shouldn't reach here");
        }
    }
};

inline constexpr ToWide toWide;

struct ToMultiByte : StringStrategySelector
{
    template <detail::WideCharString StringType>
        requires (choice<StringType> != Strategy::None)
    [[nodiscard]] std::string operator()(const StringType& str) const
    {
        constexpr Strategy strategy = choice<StringType>;

        if constexpr (detail::isOneOf(strategy,
            Strategy::WideCharBasicString,
            Strategy::WideCharStringView,
            Strategy::WideCharArray))
        {
            return stringConversion::wideToMultiByte(str);
        }
        else
        {
            static_assert(std::_Always_false<StringType>, "Shouldn't reach here");
        }
    }
};

inline constexpr ToMultiByte toMultiByte;

struct ToLower : StringStrategySelector
{
    template <typename StringType>
        requires (choice<StringType> != Strategy::None && std::is_reference_v<StringType&>)
    [[nodiscard]] auto operator()(StringType&& str) const
    {
        constexpr Strategy strategy = choice<StringType>;
        using UnrefStringType = std::remove_cvref_t<StringType>;

        const auto toLower = [&]<typename ResultType>(ResultType && result) {
            std::ranges::transform(std::forward<StringType>(str), std::forward<ResultType>(result),
                [](const auto c) {
                    return std::tolower(c);
            });
        };

        if constexpr (detail::isOneOf(strategy,
            Strategy::CharArray,
            Strategy::WideCharArray))
        {
            using ArrayDataType = std::remove_extent_t<UnrefStringType>;
            std::basic_string<ArrayDataType> result;

            toLower(std::back_inserter(result));
            return result;
        }
        else if constexpr (detail::isOneOf(strategy,
            Strategy::CharStringView,
            Strategy::WideCharStringView))
        {
            using StringViewValueType = typename UnrefStringType::value_type;
            std::basic_string<StringViewValueType> result;

            toLower(std::back_inserter(result));
            return result;
        }
        else if constexpr (detail::isOneOf(strategy,
            Strategy::CharBasicString,
            Strategy::WideCharBasicString))
        {
            toLower(std::forward<StringType>(str).begin());
            return str;
        }
        else
        {
            static_assert(std::_Always_false<StringType>, "Shouldn't reach here");
        }
    }
};

inline constexpr ToLower toLower;

struct ToUpper : StringStrategySelector
{
    template <typename StringType>
        requires (choice<StringType> != Strategy::None && std::is_reference_v<StringType&>)
    [[nodiscard]] auto operator()(StringType&& str) const
    {
        constexpr Strategy strategy = choice<StringType>;
        using UnrefStringType = std::remove_cvref_t<StringType>;

        const auto toUpper = [&]<typename ResultType>(ResultType&& result) {
            std::ranges::transform(std::forward<StringType>(str), std::forward<ResultType>(result),
                [](const auto c) {
                    return std::toupper(c);
            });
        };

        if constexpr (detail::isOneOf(strategy,
            Strategy::CharArray,
            Strategy::WideCharArray))
        {
            using ArrayDataType = std::remove_extent_t<UnrefStringType>;
            std::basic_string<ArrayDataType> result;

            toUpper(std::back_inserter(result));
            return result;
        }
        else if constexpr (detail::isOneOf(strategy,
            Strategy::CharStringView,
            Strategy::WideCharStringView))
        {
            using StringViewValueType = typename UnrefStringType::value_type;
            std::basic_string<StringViewValueType> result;

            toUpper(std::back_inserter(result));
            return result;
        }
        else if constexpr (detail::isOneOf(strategy,
            Strategy::CharBasicString,
            Strategy::WideCharBasicString))
        {
            toUpper(std::forward<StringType>(str).begin());
            return str;
        }
        else
        {
            static_assert(std::_Always_false<StringType>, "Shouldn't reach here");
        }
    }
};

inline constexpr ToUpper toUpper;

} // namespace stringUtils
