#include <fstream>
#include <codecvt>
#include <iostream>
#include <regex>
#include <fmt/format.h>
#include "utils.h"
//#include "calmsize.h"
#include "ksy_helper.h"

std::size_t
code_points(const std::string& utf8)
{
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
    std::u16string utf16 = utf16conv.from_bytes(utf8);
    return utf16.length();
}

Triple
zoneinfo(const fs::path& path)
{
    std::ifstream ifs(path, std::ifstream::binary);
    kaitai::kstream ks(&ifs);
    return detail(&ks);
}

std::string
format(const std::uintmax_t bytes)
{
    return "human_filesize(bytes)";
}

std::string
format(const double seconds)
{
    return "human_duration(seconds)";
}

std::string
format(const std::string& prefix, const fs::path& path)
{
    return "oh";
}


std::string
pad(const std::string& s, std::size_t max)
{
    // "Hello", 10 -> "Hello    "
    using namespace std::string_literals;
    if (auto cp = code_points(s); cp < max) {
        auto spaces = ""s;
        spaces.resize(max - cp, ' ');
        return s + spaces;
    }
    return s;
}

void
print_argv(char *argv, char *environ)
{
    while (argv < environ)
    {
        std::cout << ((0 == *argv) ? ' ' : *argv);
        argv ++;
    }
    std::cout << '\n';
}

std::string
strip_margin(const std::string &s)
{
    auto r = std::regex{R"(\n([ ]*)\|)"};
    return   std::regex_replace(s, r, "\n");
}
