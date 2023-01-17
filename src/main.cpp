#include <QApplication>
#include <QStandardPaths>

#include <cstdio>

#include "config.hpp"
#include "selection-window.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("browser-selector");
    app.setApplicationDisplayName(QObject::tr("ウェブブラウザの選択"));

    if (app.arguments().size() < 2)
    {
        std::fprintf(stderr, "no url provided\n");
        return 1;
    }

    selection_window sw;
    sw.setUrl(app.arguments().at(1));

    // determine location for configuration file
    const auto config_path = QStandardPaths::writableLocation(
        QStandardPaths::ConfigLocation).toStdString() + "/browser-selector.yaml";
    std::fprintf(stderr, "reading configuration from: %s\n", config_path.c_str());

    // parse the configuration file
    config_t config(config_path);
    if (!config.parse())
    {
        std::fprintf(stderr, "%s\n", config.get_last_error().c_str());
        return 1;
    }

    for (auto&& browser : config.get_browsers())
    {
        std::fprintf(stderr, "registering browser: {displayName=%s, command=%s, xdgIconName=%s}\n",
            browser.displayName.toStdString().c_str(),
            browser.command.toStdString().c_str(),
            browser.xdgIconName.toStdString().c_str());

        sw.addBrowser(browser);
    }

    sw.show();

    return app.exec();
}
