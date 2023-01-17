#pragma once

#include <string>

#include "browser.hpp"

class config_t final
{
public:
    config_t(const std::string &path);

    bool parse();

    const std::string &get_last_error() const {
        return this->last_error;
    }

    /**
     * Get a list of all available browsers.
     */
    const std::list<Browser> &get_browsers() const {
        return this->browsers;
    }

private:
    std::string path;
    std::list<Browser> browsers;
    std::string last_error;
};
