#include "selection-window.hpp"

#include <QProcess>
#include <QStandardPaths>

#include <QShortcut>
#include <QScreen>
#include <QListWidgetItem>

#include <QTextDocument>
#include <QTextBlock>

#ifdef DEBUG_BUILD
#include <QDebug>
#endif

// static unsigned int getRenderedLineCount(const QTextDocument *doc)
// {
//     unsigned int lines = 0;

//     QTextBlock tb = doc->begin();

//     while (tb.isValid())
//     {
//         if (!tb.layout())
//         {
//             continue;
//         }

//         lines += tb.layout()->lineCount();
//         tb = tb.next();
//     }

//     return lines;
// }

selection_window::selection_window(QWidget *parent)
    : QWidget(parent)
{
    // set window properties
    this->setWindowTitle(tr("ウェブブラウザの選択"));
    this->setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

    // build interface
    this->buildUi();

    // center window
    const auto geometry = this->screen()->geometry();
    this->setFixedSize(300, 500);
    this->move(
        geometry.width() / 2 - this->width() / 2,
        geometry.height() / 2 - this->height() / 2);

    // create shortcuts
    new QShortcut(Qt::Key_Escape, this, [=]{
        this->close();
    });

    connect(ui_browserList, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) {
        this->execute_browser(item);
        this->close();
    });
}

selection_window::~selection_window()
{
}

void selection_window::addBrowsers(const std::list<Browser> &browsers)
{
    for (auto&& browser : browsers)
    {
        this->addBrowser(browser);
    }
}

void selection_window::addBrowser(const Browser &browser)
{
    auto item = new QListWidgetItem(
        QIcon::fromTheme(browser.xdgIconName),
        browser.displayName,
        this->ui_browserList);
    item->setData(Qt::UserRole, QVariant::fromValue(browser));
    item->setSizeHint(QSize(64, 64));
    this->ui_browserList->addItem(item);
}

void selection_window::setUrl(const QString &url)
{
    this->ui_urlToOpen->setPlainText(url);

    // const auto fm = this->ui_urlToOpen->fontMetrics();
    // const auto lines = getRenderedLineCount(this->ui_urlToOpen->document());
    // this->ui_urlToOpen->setFixedHeight((fm.lineSpacing() + fm.height()) * lines);
}

void selection_window::execute_browser(QListWidgetItem *item) const
{
#ifdef DEBUG_BUILD
    qDebug() << item->text() << item->data(Qt::UserRole).value<Browser>();
#endif

    const auto browser = item->data(Qt::UserRole).value<Browser>();

    QProcess::startDetached(browser.command, {
        this->ui_urlToOpen->toPlainText(),
    }, QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
}
