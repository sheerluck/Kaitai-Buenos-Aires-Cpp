#pragma once

#include <filesystem>
#include "model.h"

std::size_t
code_points(const std::string& utf8);

Triple
zoneinfo(const fs::path& path);

std::string
format(const std::uintmax_t bytes);

std::string
format(const double seconds);

std::string
format(const std::string& prefix, const std::string& path);

std::string
tail(std::string const& source, size_t const length);

std::string
pad(const std::string& s, std::size_t max);

void
print_argv(char *argv, char *environ);

std::string
strip_margin(const std::string &s);
