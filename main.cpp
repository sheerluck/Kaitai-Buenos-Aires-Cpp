//#include <cstdlib>
#include <cxxopts.hpp>
#include "model.h"
#include "utils.h"
#include "rang.hpp"

void say_what_again(const std::exception& e,
                    const std::string& info = ""s)
{
    std::cout
    << rang::fgB::red
    << e.what()
    << (info.empty() ? info : "\n"s + info)
    << rang::fg::reset
    << '\n';
}

extern char **environ;

int main (int argc, char *argv[])
{
    //print_argv(*argv, *environ);
    cxxopts::Options options("mkv", "description");
    options.add_options()
        ("h,help",           "help")
        ("p,path",           "path",
          cxxopts::value<std::string>()->default_value("/usr/share/zoneinfo"));
    try
    {
        auto opt = options.parse(argc, argv);
        if (opt["help"].as<bool>())
        {
            std::cout << rang::fg::green << strip_margin(R"HELP(
            |Usage: Buenos-Aires [options]
            |Walk /usr/share/zoneinfo
            |
            |Options:
            |  -h, --help            Displays this help.
            |  -p, --path Videos     Path to zoneinfo.)HELP")
            << rang::fg::reset << "\n\n";
            return 0;
        }
        const auto path = opt["path"].as<std::string>();
        auto data = std::map<std::string, std::string>{};
        auto doptions = fs::directory_options::skip_permission_denied;
        for(const auto& p: fs::recursive_directory_iterator(fs::path{path}, doptions))
        {
            if (fs::is_regular_file(p))
            {
                try
                {
                    const auto [version, leapcnt, str] = zoneinfo(p);
                    const auto line = fmt::format(
                            "Hello, {name}! Version={version}, leap={leapcnt}, '{str}'",
                            "name"_a   =p.path().filename().string(),
                            "version"_a=version,
                            "leapcnt"_a=leapcnt,
                            "str"_a    =str);
                    const auto key = format(path, p.path().string());
                    const auto [it, ok] = data.try_emplace(key, line);
                    if (!ok) throw std::runtime_error("y u do dis to me");
                }
                catch (const std::exception& e)
                {
                    say_what_again(e, p.path().string());
                }
            }
        }
        std::cout << "\n\n";
        for (auto& [key, line] : data)
        {
            std:: cout << line << '\n';
        }
        std::cout << "\n\n";
    }
    catch (const std::exception& e)
    {
        say_what_again(e);
        return 19;
    }
}
