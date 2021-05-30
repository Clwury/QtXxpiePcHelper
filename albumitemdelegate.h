#ifndef ALBUMITEMDELEGATE_H
#define ALBUMITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QPainterPath>
#include <QBitmap>
#include <QFontMetrics>
#include <QDateTime>

#include "imageview.h"

class albumItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    albumItemDelegate(QObject *parent = 0);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ALBUMITEMDELEGATE_H
