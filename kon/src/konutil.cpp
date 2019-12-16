#include <QRect>
#include "konutil.h"

namespace Kon::Utils {
    QRect ResizeRect(QRect rect, int factor, SizeDirection dir) {
        auto size = rect.size();
        size = ResizeSize(size, factor, dir);
        rect.setSize(size);
        return rect;
    }
    QRect CenterRect(QRect rect, QSize size) {
        return QRect(rect.left() + (rect.width() - size.width())/2, rect.top() + (rect.top() - size.height())/2, size.width(), size.height());
    }
    QSize ResizeSize(QSize rect, int factor, SizeDirection dir) {
        if (dir == Out) {
            return QSize(rect.width()+factor, rect.height()+factor);
        } else {
            return QSize(rect.width()-factor, rect.height()-factor);
        }
    }
}