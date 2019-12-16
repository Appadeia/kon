#include <QStyle>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>
#include <utility>
#include <string.h>
#include <QtGlobal>
#include <QDebug>
#include <QStyleFactory>

#include "widgets/konbutton.h"

#include "konutil.h"
#include "konstyle.h"

KonStyle::KonStyle(QObject* parent)
{
    fallback = QStyleFactory::create("Adwaita-dark");
}
KonStyle::~KonStyle()
{

}
void KonStyle::drawPrimitive(PrimitiveElement prim, const QStyleOption* options, QPainter* painter, const QWidget* widget) const
{
    fallback->drawPrimitive(prim,options,painter,widget);
}
void KonStyle::drawControl(QStyle::ControlElement type, const QStyleOption* options, QPainter* painter, const QWidget* widget) const
{
    painter->save();
    defer(painter->restore());

    qDebug() << "Drawing widget" << type;

    switch(type) {
        case QStyle::CE_PushButton: return Kon::Buttons::Draw(options, painter, widget);

        default:
            qDebug() << "Falling back to Fusion for widget" << type;
            fallback->drawControl(type,options,painter,widget);
            break;
    }
}
void KonStyle::drawComplexControl(ComplexControl cont, const QStyleOptionComplex* options, QPainter* painter, const QWidget* widget) const
{
    fallback->drawComplexControl(cont, options, painter, widget);
}
QRect KonStyle::subElementRect(SubElement elm, const QStyleOption* options, const QWidget* widget) const
{
    fallback->subElementRect(elm, options, widget);
}
QRect KonStyle::subControlRect(ComplexControl cont, const QStyleOptionComplex* options, SubControl control, const QWidget* widget) const
{
    fallback->subControlRect(cont, options, control, widget);
}
QSize KonStyle::sizeFromContents( ContentsType type, const QStyleOption* options, const QSize& inSize, const QWidget* widget) const
{
    qDebug() << "Calculating size of widget" << type;
    switch(type) {
        case CT_PushButton: return Kon::Buttons::SizeFromContents(type, options, inSize, widget);

        default:
            qDebug() << "Falling back to Fusion for" << type;
            fallback->sizeFromContents(type, options, inSize, widget);
    }
}
QStyle::SubControl KonStyle::hitTestComplexControl(ComplexControl cont, const QStyleOptionComplex* options, const QPoint& point, const QWidget* widget) const
{
    fallback->hitTestComplexControl(cont, options, point, widget);
}
int KonStyle::pixelMetric(PixelMetric metric, const QStyleOption* options, const QWidget* widget) const
{
    fallback->pixelMetric(metric, options, widget);
}
int KonStyle::styleHint(StyleHint hint, const QStyleOption* options, const QWidget* widget, QStyleHintReturn* ret) const
{
    fallback->styleHint(hint, options, widget, ret);
}
QPixmap KonStyle::standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt, const QWidget *widget) const
{
    fallback->standardPixmap(standardPixmap, opt, widget);
}
QIcon KonStyle::standardIcon(StandardPixmap standardIcon, const QStyleOption *option, const QWidget *widget) const
{
    fallback->standardIcon(standardIcon, option, widget);
}
QPixmap KonStyle::generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const
{
    fallback->generatedIconPixmap(iconMode, pixmap, opt);
}
int KonStyle::layoutSpacing(QSizePolicy::ControlType control1,
                            QSizePolicy::ControlType control2, Qt::Orientation orientation,
                            const QStyleOption *option, const QWidget *widget) const
{
    fallback->layoutSpacing(control1, control2, orientation, option, widget);
}