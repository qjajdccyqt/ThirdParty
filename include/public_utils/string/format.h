#pragma once

#include <string>
#include <cctype>
#include <cassert>
#include <vector>
#include <type_traits>
#include "public_utils/data_type/any.hpp"
namespace PublicUtils
{
std::string Format(const std::string& fmt, const any& value);
/// This function implements sprintf-style formatting in a typesafe way.
/// Various variants of the function are available, supporting a
/// different number of arguments (up to six).
///
/// The formatting is controlled by the format string in fmt.
/// Format strings are quite similar to those of the std::printf() function, but
/// there are some minor differences.
///
/// The format string can consist of any sequence of characters; certain
/// characters have a special meaning. Characters without a special meaning
/// are copied verbatim to the result. A percent sign (%) marks the beginning
/// of a format specification. Format specifications have the following syntax:
///
///   %[<index>][<flags>][<width>][.<precision>][<modifier>]<type>
///
/// Index, flags, width, precision and prefix are optional. The only required part of
/// the format specification, apart from the percent sign, is the type.
///
/// The optional index argument has the format "[<n>]" and allows to
/// address an argument by its zero-based position (see the example below).
///
/// Following are valid type specifications and their meaning:
///
///   * b boolean (true = 1, false = 0)
///   * c character
///   * d signed decimal integer
///   * i signed decimal integer
///   * o unsigned octal integer
///   * u unsigned decimal integer
///   * x unsigned hexadecimal integer (lower case)
///   * X unsigned hexadecimal integer (upper case)
///   * e signed floating-point value in the form [-]d.dddde[<sign>]dd[d]
///   * E signed floating-point value in the form [-]d.ddddE[<sign>]dd[d]
///   * f signed floating-point value in the form [-]dddd.dddd
///   * s std::string
///   * z std::size_t
///
/// The following flags are supported:
///
///   * - left align the result within the given field width
///   * + prefix the output value with a sign (+ or -) if the output value is of a signed type
///   * 0 if width is prefixed with 0, zeros are added until the minimum width is reached
///   * # For o, x, X, the # flag prefixes any nonzero output value with 0, 0x, or 0X, respectively;
///     for e, E, f, the # flag forces the output value to contain a decimal point in all cases.
///
/// The following modifiers are supported:
///
///   * (none) argument is char (c), int (d, i), unsigned (o, u, x, X) double (e, E, f, g, G) or string (s)
///   * l      argument is long (d, i), unsigned long (o, u, x, X) or long double (e, E, f, g, G)
///   * L      argument is long long (d, i), unsigned long long (o, u, x, X)
///   * h      argument is short (d, i), unsigned short (o, u, x, X) or float (e, E, f, g, G)
///   * ?      argument is any signed or unsigned char, int, short, long, or 64-bit integer (d, i, o, x, X)
///
/// The width argument is a nonnegative decimal integer or '*' with an additional nonnegative integer value
/// preceding the value to be formated, controlling the minimum number of characters printed.
/// If the number of characters in the output value is less than the specified width, blanks or
/// leading zeros are added, according to the specified flags (-, +, 0).
///
/// Precision is a nonnegative decimal integer or '*' with an additional nonnegative integer value preceding
/// the value to be formated, preceded by a period (.), which specifies the number of characters
/// to be printed, the number of decimal places, or the number of significant digits.
///
/// Throws an InvalidArgumentException if an argument index is out of range.
///
/// Starting with release 1.4.3, an argument that does not match the format
/// specifier no longer results in a BadCastException. The string [ERRFMT] is
/// written to the result string instead.
///
/// If there are more format specifiers than values, the format specifiers without a corresponding value
/// are copied verbatim to output.
///
/// If there are more values than format specifiers, the superfluous values are ignored.
///
/// Usage Examples:
///     std::string s1 = Format("The answer to life, the universe, and everything is %d", 42);
///     std::string s2 = Format("second: %[1]d, first: %[0]d", 1, 2);

void Format(std::string& result, const char *fmt, const std::vector<any>& values);
/// Supports a variable number of arguments and is used by
/// all other variants of Format().

void Format(std::string& result, const std::string& fmt, const std::vector<any>& values);
/// Supports a variable number of arguments and is used by
/// all other variants of Format().

template <typename T, typename... Args>
void Format(std::string &result, const std::string &fmt, T arg1, Args... args)
/// Appends the formatted string to result.
{
    std::vector<any> values;
    values.push_back(arg1);
    values.insert(values.end(), { args... });
    Format(result, fmt, values);
}

template <typename FMT, typename T, typename... Args,
    typename std::enable_if< std::is_const< typename std::remove_reference<FMT>::type >::value, int >::type = 0>
    std::string Format(FMT &fmt, T arg1, Args... args)
    /// Returns the formatted string.
{
    std::vector<any> values;
    values.push_back(arg1);
    values.insert(values.end(), { args... });
    std::string result;
    Format(result, fmt, values);
    return result;
}
}
