#include "selection-window.hpp"

void selection_window::buildUi()
{
    ui_layout = new QVBoxLayout(this);
    ui_layout->setContentsMargins(5,5,5,5);
    ui_layout->setSpacing(5);
    ui_layout->setSizeConstraint(QLayout::SetMaximumSize);
    this->setLayout(ui_layout);

    ui_urlToOpen = new QPlainTextEdit();
    ui_urlToOpen->setTextInteractionFlags(Qt::TextSelectableByMouse);
    ui_urlToOpen->setReadOnly(true);
    ui_urlToOpen->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    ui_urlToOpen->setWordWrapMode(QTextOption::WrapAnywhere);
    ui_urlToOpen->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui_layout->addWidget(ui_urlToOpen);
    this->setUrl("");

    ui_browserList = new QListWidget();
    ui_browserList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui_browserList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui_browserList->setIconSize(QSize(60, 60));
    ui_browserList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui_layout->addWidget(ui_browserList);
}
