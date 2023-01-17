#pragma once

#include <QString>
#include <QMetaType>

#ifdef DEBUG_BUILD
#include <QDebug>
#endif

struct Browser final
{
    QString displayName;
    QString command;
    QString xdgIconName;
};

Q_DECLARE_METATYPE(Browser);

#ifdef DEBUG_BUILD
inline QDebug operator<< (QDebug dbg, const Browser &browser)
{
    dbg << QString("Browser{displayName=\"%1\", command=\"%2\"").arg(browser.displayName, browser.command);
    return dbg;
}
#endif
