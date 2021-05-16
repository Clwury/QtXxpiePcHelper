#ifndef ITEMDELEGATE_H
#define ITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>

#include "imageview.h"

class ItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ItemDelegate();
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ITEMDELEGATE_H
