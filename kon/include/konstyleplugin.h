#pragma once

#include <QStringList>
#include <QStyle>
#include <QStylePlugin>
#include <QtPlugin>
#include "konstyle.h"

class KonStylePlugin : public QStylePlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "kon.json")

public:
    KonStylePlugin(QObject *parent = nullptr);

    QStringList keys() const;
    QStyle* create(const QString &key) override;
};