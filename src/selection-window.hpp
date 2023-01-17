#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QListWidget>
#include <QList>

#include "browser.hpp"

class selection_window final : public QWidget
{
    Q_OBJECT

public:
    explicit selection_window(QWidget *parent = nullptr);
    ~selection_window();

    void addBrowsers(const std::list<Browser> &browsers);
    void addBrowser(const Browser &browser);
    void setUrl(const QString &url);

private:
    // interface
    void buildUi();
    QVBoxLayout *ui_layout;
    QPlainTextEdit *ui_urlToOpen;
    QListWidget *ui_browserList;

    void execute_browser(QListWidgetItem *item) const;
};
