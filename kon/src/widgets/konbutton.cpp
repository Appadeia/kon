#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>

#include "widgets/konbutton.h"
#include "konconsts.h"
#include "konutil.h"

namespace Kon::Buttons {
    QSize SizeFromContents ( QStyle::ContentsType type, const QStyleOption* options, const QSize& inSize, const QWidget* widget ) {
        // We want to cast our style options to button options so we can get button-specific things.
        const auto buttonOptions(qstyleoption_cast<const QStyleOptionButton*>(options));

        // If we don't have any options, we should probably let the button do whatever it wants to.
        if (!buttonOptions) {
            return inSize;
        }

        // This is what we'll be manipulating to return an output.
        QSize returnSize;

        // Let's get some convenience things going here.
        const bool buttonHasText = (!buttonOptions->text.isEmpty());
        const bool buttonIsFlat = (buttonOptions->features & QStyleOptionButton::Flat);
        const bool buttonHasIcon (!buttonOptions->icon.isNull());

        if (!buttonHasText && !buttonHasIcon) {
            // We don't have text or an icon,
            // so we'll use the button's request
            // as a starting point.
            returnSize = inSize;
        } else {
            // We want to do our own maths for button sizing
            // So we can use the same maths everywhere

            if (buttonHasText) {
                // Let's use the text size as a baseline size for our button.
                returnSize = buttonOptions->fontMetrics.size( Qt::TextShowMnemonic, buttonOptions->text );
            }

            if (buttonHasIcon) {
                // Let's see what the size of the icon is...
                QSize buttonIconSize = buttonOptions->iconSize;

                // If our button icon size isn't valid, then we should probably
                // use one that is valid.
                if (!buttonIconSize.isValid()) {
                    buttonIconSize = QSize(Constants::IconSize, Constants::IconSize);
                }

                // We want to size the button to its contents, so we'll
                // size to the larger of the following two: icons or text
                returnSize.setHeight(qMax(returnSize.height(), buttonIconSize.height()));
                
                // Expand the width by the width of the icon...
                returnSize.rwidth() += buttonIconSize.width();
            }
        }

        // Let's get our margins...
        returnSize = Kon::Utils::ResizeSize(returnSize, Constants::Button__Margin, Utils::Out);

        // Check for minimum size.
        returnSize.setHeight(qMax(returnSize.height(), Constants::Button__MinimumDimension));
        returnSize.setWidth(qMax(returnSize.width(), Constants::Button__MinimumDimension));

        // Make room for the borders...
        returnSize = Kon::Utils::ResizeSize(returnSize, Constants::Button__BorderSize, Utils::Out);

        return QSize(returnSize.width(), returnSize.height());
    }
    void Draw(const QStyleOption* options, QPainter* painter, const QWidget* widget) {
        // We want to cast our style options to button options so we can get button-specific things.
        const auto buttonOptions(qstyleoption_cast<const QStyleOptionButton*>(options));

        // If we don't have any options, just give up.
        if (!buttonOptions) {
            return;
        }

        // Some convenience things for us here
        const QRect& buttonRect(options->rect);
        const QPalette& buttonPalette(options->palette);
        const bool buttonIsFlat(buttonOptions->features & QStyleOptionButton::Flat);

        // Some stuff about the button's contents
        const bool buttonHasText(!buttonOptions->text.isEmpty());
        const bool buttonHasIcon(!buttonOptions->icon.isNull());

        // The state of the button
        const QStyle::State& buttonState(options->state);
        const bool buttonEnabled(buttonState & QStyle::State_Enabled);
        const bool buttonPressed(buttonState & QStyle::State_Sunken);
        const bool buttonHovering(buttonState & QStyle::State_MouseOver);
        const bool buttonFocused(buttonEnabled && buttonState & QStyle::State_HasFocus);

        QPalette::ColorRole buttonTextRole;
        
        if (buttonIsFlat) {
            buttonTextRole = QPalette::WindowText;
        } else {
            buttonTextRole = QPalette::ButtonText;
        }

        // Let's see what the size of the icon is...
        QSize buttonIconSize;

        if (buttonHasIcon) {
            buttonIconSize = buttonOptions->iconSize;
            // If our button icon size isn't valid, then we should probably
            // use one that is valid.
            if (!buttonIconSize.isValid()) {
                buttonIconSize = QSize(Constants::IconSize, Constants::IconSize);
            }
        }

        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        if (!buttonIsFlat) {
            painter->setBrush(widget->palette().color(QPalette::Button));
            painter->setPen(QPen(widget->palette().color(QPalette::Button).lighter(), Constants::Button__BorderSize));

            if(buttonFocused) {
                painter->setPen(QPen(widget->palette().color(QPalette::Highlight), Constants::Button__BorderSize));
            }
            if(buttonPressed) {
                painter->setBrush(widget->palette().color(QPalette::Button).darker());
            }
            auto rect = Kon::Utils::ResizeRect(buttonRect, Constants::Button__BorderSize, Utils::In);
            painter->drawRoundedRect(QRect(rect.x()+Constants::Button__BorderSize/2,rect.y()+Constants::Button__BorderSize/2,rect.width(),rect.height()), 10, 10);
        } else {
            if (buttonFocused) {
                painter->setPen(QPen(widget->palette().color(QPalette::Highlight), Constants::Button__BorderSize));
            }
            if(buttonPressed) {
                painter->setBrush(widget->palette().color(QPalette::Button).darker());
            }
            if(buttonFocused || buttonPressed) {
                auto rect = Kon::Utils::ResizeRect(buttonRect, Constants::Button__BorderSize, Utils::In);
                painter->drawRoundedRect(QRect(rect.x()+Constants::Button__BorderSize/2,rect.y()+Constants::Button__BorderSize/2,rect.width(),rect.height()), 10, 10);
            }
        }

        if (buttonHasText) {
            qDebug() << "printing text" << buttonOptions->text;
            painter->setPen(widget->palette().color(buttonTextRole));
            painter->drawText(buttonRect, Qt::AlignCenter, buttonOptions->text);
        }
    }
}