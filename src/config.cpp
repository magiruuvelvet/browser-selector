#include "config.hpp"

#include <yaml-cpp/yaml.h>

namespace {

static inline const QString read_QString_from_YAML(const YAML::Node &node, const std::string &key)
{
    return QString::fromStdString(node[key].as<std::string>());
}

} // anonymous namespace

config_t::config_t(const std::string &path)
    : path(path)
{
}

bool config_t::parse()
{
    try {
        const auto browsers = YAML::LoadFile(this->path);
        for (auto&& browser : browsers)
        {
            this->browsers.emplace_back(Browser{
                .displayName = read_QString_from_YAML(browser, "displayName"),
                .command = read_QString_from_YAML(browser, "command"),
                .xdgIconName = read_QString_from_YAML(browser, "xdgIconName"),
            });
        }
    } catch (const YAML::ParserException &e) {
        this->last_error = e.what();
        return false;
    } catch (const YAML::BadFile &e) {
        this->last_error = e.what();
        return false;
    }

    return true;
}
