#pragma once

#include <QStyle>
#include <libcss/libcss.h>


class KonStyle : public QStyle {
    Q_OBJECT

public:
        KonStyle(QObject* parent = nullptr);
        ~KonStyle();

        /*
        *   Primitives, Controls, and Complex Controls
        */
        void drawPrimitive( PrimitiveElement, const QStyleOption*, QPainter*, const QWidget* ) const override;
        void drawControl( ControlElement, const QStyleOption*, QPainter*, const QWidget* ) const override;
        void drawComplexControl( ComplexControl, const QStyleOptionComplex*, QPainter*, const QWidget* ) const override;

        /*
        *   Stuff that draws rects.
        */
        QRect subElementRect( SubElement, const QStyleOption*, const QWidget* ) const override;
        QRect subControlRect( ComplexControl, const QStyleOptionComplex*, SubControl, const QWidget* ) const override;
        QSize sizeFromContents( ContentsType, const QStyleOption*, const QSize&, const QWidget* ) const override;
        SubControl hitTestComplexControl( ComplexControl, const QStyleOptionComplex*, const QPoint&, const QWidget* ) const override;

        /*
        *   Numbers and stuff.
        */
        int pixelMetric(PixelMetric, const QStyleOption* = nullptr, const QWidget* = nullptr) const override;
        int styleHint(StyleHint, const QStyleOption* = nullptr, const QWidget* = nullptr, QStyleHintReturn* = nullptr) const override;

        /*
        *   Default pixmaps.
        */
        QPixmap standardPixmap(StandardPixmap standardPixmap, const QStyleOption *opt = nullptr, const QWidget *widget = nullptr) const override;
        QIcon standardIcon(StandardPixmap standardIcon, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
        QPixmap generatedIconPixmap(QIcon::Mode iconMode, const QPixmap &pixmap, const QStyleOption *opt) const override;

        /*
        *   Spacing
        */
        int layoutSpacing(QSizePolicy::ControlType control1,
                          QSizePolicy::ControlType control2, Qt::Orientation orientation,
                          const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;

        QStyle* fallback;
private:
        css_stylesheet* stylesheet;
        css_select_ctx* select_ctx;
};