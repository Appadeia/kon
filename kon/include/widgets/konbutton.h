#pragma once

#include <QStyle>
#include <QSize>

namespace Kon::Buttons {
    QSize SizeFromContents(QStyle::ContentsType, const QStyleOption*, const QSize&, const QWidget*);
    void Draw(const QStyleOption*, QPainter*, const QWidget*);
}