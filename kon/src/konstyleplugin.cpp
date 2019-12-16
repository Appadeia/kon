#include <QStringList>
#include <QStyle>
#include "konstyleplugin.h"
#include "konstyle.h"

KonStylePlugin::KonStylePlugin(QObject *parent)
{

}
QStringList KonStylePlugin::keys() const
{
    return QStringList() << QStringLiteral( "Kon" );
}

QStyle *KonStylePlugin::create(const QString &key)
{
    return new KonStyle;
}